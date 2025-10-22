#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
// libxml2 pentru XML
#include <libxml/parser.h>
#include <libxml/tree.h>
#define PORT 12345
#define BUFFER_SIZE 1024

typedef struct Client {
    int socket;
    char nume[50];
    char tip[20];
    char profil[10];
    int authenticated;
    struct Client *next;
} Client;
Client *clients_list = NULL;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
void add_client(int client_socket) {
    Client *new_client = (Client *)malloc(sizeof(Client));
    if (!new_client) {
        perror("Eroare la alocarea memoriei pentru noul client");
        return;
    }
    new_client->socket = client_socket;
    new_client->nume[0] = '\0'; 
    new_client->tip[0] = '\0';
    new_client->profil[0] = '\0';
    new_client->authenticated = 0; 
    new_client->next = NULL;

    pthread_mutex_lock(&clients_mutex);
    new_client->next = clients_list;
    clients_list = new_client;
    pthread_mutex_unlock(&clients_mutex);
}
void authenticate_client(int client_socket, const char *nume, const char *tip, const char *profil) {
    pthread_mutex_lock(&clients_mutex);
    Client *curr = clients_list;
    while (curr != NULL) {
        if (curr->socket == client_socket) {
            strncpy(curr->nume, nume, sizeof(curr->nume) - 1);
            curr->nume[sizeof(curr->nume) - 1] = '\0';
            strncpy(curr->tip, tip, sizeof(curr->tip) - 1);
            curr->tip[sizeof(curr->tip) - 1] = '\0';
            strncpy(curr->profil, profil, sizeof(curr->profil) - 1);
            curr->profil[sizeof(curr->profil) - 1] = '\0';
            curr->authenticated = 1;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&clients_mutex);
}
void remove_client(int client_socket) {
    pthread_mutex_lock(&clients_mutex);
    Client *prev = NULL;
    Client *curr = clients_list;
    while (curr != NULL) {
        if (curr->socket == client_socket) {
            if (prev == NULL) {
                clients_list = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    pthread_mutex_unlock(&clients_mutex);
}
void send_private_message(const char *sender, const char *destinatar, const char *text_mesaj) {
    pthread_mutex_lock(&clients_mutex);
    Client *curr = clients_list;
    while (curr != NULL) {
        if (curr->authenticated && strcmp(curr->nume, destinatar) == 0) {
            char mesaj[BUFFER_SIZE];
            snprintf(mesaj, sizeof(mesaj), "[Mesaj Privat de la %s]: %s\n", sender, text_mesaj);
            send(curr->socket, mesaj, strlen(mesaj), 0);
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&clients_mutex);
}
int is_friend(const char *username, const char *friend_name) {
    xmlDocPtr doc = xmlParseFile("users.xml");
    if (!doc) {
        fprintf(stderr, "[Server] Eroare la parsarea XML.\n");
        return 0;
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (!root) {
        xmlFreeDoc(doc);
        return 0;
    }

    for (xmlNodePtr userNode = root->children; userNode; userNode = userNode->next) {
        if (userNode->type == XML_ELEMENT_NODE && xmlStrcmp(userNode->name, (const xmlChar*)"user") == 0) {
            xmlChar *nameAttr = xmlGetProp(userNode, (const xmlChar*)"name");
            if (nameAttr && strcmp((const char *)nameAttr, username) == 0) {
                xmlNodePtr friendsNode = NULL;
                for (xmlNodePtr child = userNode->children; child; child = child->next) {
                    if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar*)"friends") == 0) {
                        friendsNode = child;
                        break;
                    }
                }
                if (friendsNode) {
                    for (xmlNodePtr friendNode = friendsNode->children; friendNode; friendNode = friendNode->next) {
                        if (friendNode->type == XML_ELEMENT_NODE && xmlStrcmp(friendNode->name, (const xmlChar*)"friend") == 0) {
                            xmlChar *friendName = xmlGetProp(friendNode, (const xmlChar*)"name");
                            if (friendName && strcmp((const char *)friendName, friend_name) == 0) {
                                xmlFree(friendName);
                                xmlFree(nameAttr);
                                xmlFreeDoc(doc);
                                return 1;
                            }
                            if (friendName) xmlFree(friendName);
                        }
                    }
                }
            }
            if (nameAttr) xmlFree(nameAttr);
        }
    }
    xmlFreeDoc(doc);
    return 0;
}

void send_notification_to_all(const char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    Client *curr = clients_list;
    while (curr != NULL) {
        if (curr->authenticated && curr->socket != sender_socket) {
            send(curr->socket, message, strlen(message), 0);
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&clients_mutex);
}
void send_notification_to_friends(const char *username, const char *message) {
    pthread_mutex_lock(&clients_mutex);
    xmlDocPtr doc = xmlParseFile("users.xml");
    if (doc) {
        xmlNodePtr root = xmlDocGetRootElement(doc);
        for (xmlNodePtr userNode = root->children; userNode; userNode = userNode->next) {
            if (userNode->type == XML_ELEMENT_NODE && xmlStrcmp(userNode->name, (const xmlChar *)"user") == 0) {
                xmlChar *nameAttr = xmlGetProp(userNode, (const xmlChar *)"name");
                if (nameAttr && strcmp((const char *)nameAttr, username) == 0) {
                    xmlNodePtr friendsNode = NULL;
                    for (xmlNodePtr child = userNode->children; child; child = child->next) {
                        if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"friends") == 0) {
                            friendsNode = child;
                            break;
                        }
                    }
                    if (friendsNode) {
                        for (xmlNodePtr friendNode = friendsNode->children; friendNode; friendNode = friendNode->next) {
                            if (friendNode->type == XML_ELEMENT_NODE && xmlStrcmp(friendNode->name, (const xmlChar *)"friend") == 0) {
                                xmlChar *friendName = xmlGetProp(friendNode, (const xmlChar *)"name");
                                if (friendName) {
                                    Client *client = clients_list;
                                    while (client != NULL) {
                                        if (client->authenticated && strcmp(client->nume, (const char *)friendName) == 0) {
                                            send(client->socket, message, strlen(message), 0);
                                        }
                                        client = client->next;
                                    }
                                    xmlFree(friendName);
                                }
                            }
                        }
                    }
                }
                xmlFree(nameAttr);
            }
        }
        xmlFreeDoc(doc);
    }
    pthread_mutex_unlock(&clients_mutex);
}
void send_notification_to_close_friends(const char *username, const char *message) {
    pthread_mutex_lock(&clients_mutex);
    xmlDocPtr doc = xmlParseFile("users.xml");
    if (doc) {
        xmlNodePtr root = xmlDocGetRootElement(doc);
        for (xmlNodePtr userNode = root->children; userNode; userNode = userNode->next) {
            if (userNode->type == XML_ELEMENT_NODE && xmlStrcmp(userNode->name, (const xmlChar *)"user") == 0) {
                xmlChar *nameAttr = xmlGetProp(userNode, (const xmlChar *)"name");
                if (nameAttr && strcmp((const char *)nameAttr, username) == 0) {
                    xmlNodePtr friendsNode = NULL;
                    for (xmlNodePtr child = userNode->children; child; child = child->next) {
                        if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"friends") == 0) {
                            friendsNode = child;
                            break;
                        }
                    }
                    if (friendsNode) {
                        for (xmlNodePtr friendNode = friendsNode->children; friendNode; friendNode = friendNode->next) {
                            if (friendNode->type == XML_ELEMENT_NODE && xmlStrcmp(friendNode->name, (const xmlChar *)"friend") == 0) {
                                xmlChar *friendName = xmlGetProp(friendNode, (const xmlChar *)"name");
                                xmlChar *friendType = xmlGetProp(friendNode, (const xmlChar *)"type");
                                if (friendName && friendType && strcmp((const char *)friendType, "close") == 0) {
                                    Client *client = clients_list;
                                    while (client != NULL) {
                                        if (client->authenticated && strcmp(client->nume, (const char *)friendName) == 0) {
                                            send(client->socket, message, strlen(message), 0);
                                        }
                                        client = client->next;
                                    }
                                }
                                if (friendName) xmlFree(friendName);
                                if (friendType) xmlFree(friendType);
                            }
                        }
                    }
                }
                xmlFree(nameAttr);
            }
        }
        xmlFreeDoc(doc);
    }
    pthread_mutex_unlock(&clients_mutex);
}
void initialize_xml_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        FILE *fnew = fopen(filename, "w");
        if (fnew) {
            fprintf(fnew, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<users>\n</users>\n");
            fclose(fnew);
        }
    } else {
        fclose(f);
    }
}
char *strtrim(char *str) {
    if (!str) return str;
    while (isspace((unsigned char)*str)) 
        str++;
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) 
        end--;
    *(end + 1) = '\0';
    return str;
}
void save_xml_to_file(xmlNodePtr node, FILE *file, int indent_level) {
    if (!node) return;
    char indent[1024];
    memset(indent, ' ', indent_level * 2);
    indent[indent_level * 2] = '\0';
    for (xmlNodePtr current = node; current; current = current->next) {
        if (current->type == XML_ELEMENT_NODE) {
            fprintf(file, "%s<%s", indent, current->name);
            for (xmlAttrPtr attr = current->properties; attr; attr = attr->next) {
                xmlChar *value = xmlNodeGetContent(attr->children);
                fprintf(file, " %s=\"%s\"", attr->name, value);
                xmlFree(value);
            }
            if (!current->children) {
                fprintf(file, "/>\n");
            } else {
                fprintf(file, ">\n");
                save_xml_to_file(current->children, file, indent_level + 1);
                fprintf(file, "%s</%s>\n", indent, current->name);
            }
        } else if (current->type == XML_TEXT_NODE) {
            xmlChar *content = xmlNodeGetContent(current);
            if (content && xmlStrlen(content) > 0) {
                char *trimmed_content = strtrim((char *)content);
                if (strlen(trimmed_content) > 0) {
                    fprintf(file, "%s%s\n", indent, trimmed_content);
                }
            }
            xmlFree(content);
        }
    }
}
int write_xml(xmlDocPtr doc, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "[Server] Eroare la deschiderea fișierului: %s\n", filename);
        return -1;
    }
    fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    save_xml_to_file(xmlDocGetRootElement(doc), file, 0);
    fclose(file);
    printf("[Server] Fișierul XML a fost salvat: %s\n", filename);
    return 0;
}
xmlNodePtr get_or_create_user(xmlDocPtr doc, const char *username, const char *tip_user, const char *profil) {
    xmlNodePtr root = xmlDocGetRootElement(doc);
    if (!root) return NULL;
    xmlNodePtr userNode = NULL, prevNode = NULL;
    for (xmlNodePtr node = root->children; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE && xmlStrcmp(node->name, (const xmlChar*)"user") == 0) {
            xmlChar *nameAttr = xmlGetProp(node, (const xmlChar*)"name");
            if (nameAttr) {
                if (strcmp((const char*)nameAttr, username) == 0) {
                    userNode = node; 
                } else if (strcmp((const char*)nameAttr, username) > 0) {
                    break; 
                }
                xmlFree(nameAttr);
            }
        }
        prevNode = node;
    }
    if (!userNode) {
        userNode = xmlNewNode(NULL, BAD_CAST "user");
        xmlNewProp(userNode, BAD_CAST "name", BAD_CAST username);
        xmlNewProp(userNode, BAD_CAST "type", BAD_CAST tip_user);
        xmlNewProp(userNode, BAD_CAST "profile", BAD_CAST profil);
        xmlNewChild(userNode, NULL, BAD_CAST "events", NULL);
        xmlNewChild(userNode, NULL, BAD_CAST "friends", NULL);
        if (prevNode) {
            xmlAddNextSibling(prevNode, userNode);
        } else {
            xmlAddChild(root, userNode);
        }
    }

    return userNode;
}
void add_user_event(const char *filename, const char *username, const char *tip_user, const char *profil, const char *event_text, const char *event_type) {
    xmlDocPtr doc = xmlParseFile(filename);
    if (!doc) {
        fprintf(stderr, "[Server] Eroare la parsarea XML.\n");
        return;
    }
    xmlNodePtr userNode = get_or_create_user(doc, username, tip_user, profil);
    if (!userNode) {
        xmlFreeDoc(doc);
        return;
    }
    xmlNodePtr eventsNode = NULL;
    for (xmlNodePtr ch = userNode->children; ch; ch = ch->next) {
        if (ch->type == XML_ELEMENT_NODE && xmlStrcmp(ch->name, (const xmlChar*)"events") == 0) {
            eventsNode = ch;
            break;
        }
    }
    if (!eventsNode) {
        eventsNode = xmlNewChild(userNode, NULL, BAD_CAST "events", NULL);
    }
    xmlNodePtr newEvent = xmlNewChild(eventsNode, NULL, BAD_CAST "event", BAD_CAST event_text);
    xmlNewProp(newEvent, BAD_CAST "type", BAD_CAST event_type);
    if (write_xml(doc, filename) == -1) {
        fprintf(stderr, "[Server] Salvarea fișierului XML a eșuat: %s\n", filename);
    }
    xmlFreeDoc(doc);
}

void add_friend_xml(const char *filename, const char *username, const char *tip_user, const char *profil, const char *friend_name, const char *friend_type) {
    xmlDocPtr doc = xmlParseFile(filename);
    if (!doc) {
        fprintf(stderr, "[Server] Eroare la parsarea fișierului XML.\n");
        return;
    }
    xmlNodePtr userNode = get_or_create_user(doc, username, tip_user, profil);
    if (!userNode) {
        xmlFreeDoc(doc);
        return;
    }
    xmlNodePtr friendsNode = NULL;
    for (xmlNodePtr ch = userNode->children; ch; ch = ch->next) {
        if (ch->type == XML_ELEMENT_NODE && xmlStrcmp(ch->name, (const xmlChar*)"friends") == 0) {
            friendsNode = ch;
            break;
        }
    }
    if (!friendsNode) {
        friendsNode = xmlNewChild(userNode, NULL, BAD_CAST "friends", NULL);
    }
    xmlNodePtr newFriend = xmlNewChild(friendsNode, NULL, BAD_CAST "friend", NULL);
    xmlNewProp(newFriend, BAD_CAST "name", BAD_CAST friend_name);
    xmlNewProp(newFriend, BAD_CAST "type", BAD_CAST friend_type);
    add_user_event(filename, username, tip_user, profil, "AdaugarePrieten", "friend");
    write_xml(doc, filename);
    xmlFreeDoc(doc);
}
void add_stire_xml(const char *filename, const char *username, const char *tip_user, const char *profil, const char *destinatar, const char *text_stire) {
    xmlDocPtr doc = xmlParseFile(filename);
    if (!doc) {
        fprintf(stderr, "[Server] Eroare la parsarea XML.\n");
        return;
    }
    xmlNodePtr userNode = get_or_create_user(doc, username, tip_user, profil);
    if (!userNode) {
        xmlFreeDoc(doc);
        return;
    }
    xmlNodePtr eventsNode = NULL;
    for (xmlNodePtr ch = userNode->children; ch; ch = ch->next) {
        if (ch->type == XML_ELEMENT_NODE && xmlStrcmp(ch->name, (const xmlChar*)"events") == 0) {
            eventsNode = ch;
            break;
        }
    }
    if (!eventsNode) {
        eventsNode = xmlNewChild(userNode, NULL, BAD_CAST "events", NULL);
    }
    char msg[512];
    snprintf(msg, sizeof(msg), "Stire trimisa catre %s: %s", destinatar, text_stire);
    xmlNodePtr newEvent = xmlNewChild(eventsNode, NULL, BAD_CAST "event", BAD_CAST msg);
    xmlNewProp(newEvent, BAD_CAST "type", BAD_CAST "stire");
    write_xml(doc, filename);
    xmlFreeDoc(doc);
}
void set_user_profile(const char *filename, const char *username, const char *tip_user, const char *old_profil, const char *new_profil) {
    xmlDocPtr doc = xmlParseFile(filename);
    if (!doc) {
        fprintf(stderr, "[Server] Eroare la parsarea XML.\n");
        return;
    }
    xmlNodePtr userNode = get_or_create_user(doc, username, tip_user, old_profil);
    if (!userNode) {
        xmlFreeDoc(doc);
        return;
    }
    xmlSetProp(userNode, BAD_CAST "profile", BAD_CAST new_profil);
    xmlNodePtr eventsNode = NULL;
    for (xmlNodePtr ch = userNode->children; ch; ch = ch->next) {
        if (ch->type == XML_ELEMENT_NODE && xmlStrcmp(ch->name, (const xmlChar*)"events") == 0) {
            eventsNode = ch;
            break;
        }
    }
    if (!eventsNode) {
        eventsNode = xmlNewChild(userNode, NULL, BAD_CAST "events", NULL);
    }
    char msg[256];
    snprintf(msg, sizeof(msg), "SetareProfil => %s", new_profil);
    xmlNodePtr newEvent = xmlNewChild(eventsNode, NULL, BAD_CAST "event", BAD_CAST msg);
    xmlNewProp(newEvent, BAD_CAST "type", BAD_CAST "profil");
    write_xml(doc, filename);
    xmlFreeDoc(doc);
}
 pthread_mutex_t db_mutex; 
void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);
    char buffer[BUFFER_SIZE];
    char nume[50], tip[20], profil[10];
    int autentificat = 0;
    add_client(client_socket);
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            printf("[Server] Client deconectat.\n");
            if (autentificat) {
                pthread_mutex_lock(&db_mutex);
                xmlDocPtr doc = xmlParseFile("users.xml");
                if (doc) {
                    xmlNodePtr userNode = get_or_create_user(doc, nume, tip, profil);
                    if (userNode) {
                        xmlUnsetProp(userNode, BAD_CAST "authenticated");
                        write_xml(doc, "users.xml");
                    }
                    xmlFreeDoc(doc);
                }
                pthread_mutex_unlock(&db_mutex);
                remove_client(client_socket);
            }
            close(client_socket);
            return NULL;
        }
        buffer[bytes_received] = '\0';
        buffer[strcspn(buffer, "\r\n")] = '\0';
        printf("[Server] Comandă primită: %s\n", buffer);
        char comanda[50];
        sscanf(buffer, "%s", comanda);
        if (strcmp(comanda, "Autentificare") == 0) {
    if (autentificat) {
        snprintf(buffer, sizeof(buffer), "[Server] Deja autentificat ca %s.\n", nume);
    } else {
        if (sscanf(buffer, "Autentificare %s %s %s", nume, tip, profil) != 3) {
            strcpy(buffer, "Format: Autentificare <nume> <tip> <public/privat>\n");
        } else {
            autentificat = 1;
            pthread_mutex_lock(&db_mutex);
            xmlDocPtr doc = xmlParseFile("users.xml");
            if (doc) {
                xmlNodePtr userNode = get_or_create_user(doc, nume, tip, profil);
                if (userNode) {
                    xmlSetProp(userNode, BAD_CAST "authenticated", BAD_CAST "true");
                    write_xml(doc, "users.xml");
                }
                xmlFreeDoc(doc);
            }
            pthread_mutex_unlock(&db_mutex);
            snprintf(buffer, sizeof(buffer), "[Server] Autentificare reușită: %s (%s, %s)\n", nume, tip, profil);
            authenticate_client(client_socket, nume, tip, profil);
        }
    }
    send(client_socket, buffer, strlen(buffer), 0);
}
        else if (strcmp(comanda, "MesajPrivat") == 0) {
    if (!autentificat) {
        strcpy(buffer, "Trebuie să vă autentificați pentru a trimite mesaje private.\n");
    } else {
        char destinatar[50];
        char text_mesaj[512];
        if (sscanf(buffer, "MesajPrivat %s %[^\n]", destinatar, text_mesaj) != 2) {
            strcpy(buffer, "Format: MesajPrivat <destinatar> <text_mesaj>\n");
        } else {
            pthread_mutex_lock(&db_mutex);
            xmlDocPtr doc = xmlParseFile("users.xml");
            int destinatar_autentificat = 0;
            char profil_destinatar[10] = "";
            if (doc) {
                xmlNodePtr root = xmlDocGetRootElement(doc);
                for (xmlNodePtr userNode = root->children; userNode; userNode = userNode->next) {
                    if (userNode->type == XML_ELEMENT_NODE && xmlStrcmp(userNode->name, (const xmlChar*)"user") == 0) {
                        xmlChar *nameAttr = xmlGetProp(userNode, (const xmlChar*)"name");
                        if (nameAttr && strcmp((const char *)nameAttr, destinatar) == 0) {
                            xmlChar *authAttr = xmlGetProp(userNode, (const xmlChar*)"authenticated");
                            xmlChar *profileAttr = xmlGetProp(userNode, (const xmlChar*)"profile");
                            if (authAttr && strcmp((const char *)authAttr, "true") == 0) {
                                destinatar_autentificat = 1;
                                if (profileAttr) {
                                    strncpy(profil_destinatar, (const char *)profileAttr, sizeof(profil_destinatar) - 1);
                                    profil_destinatar[sizeof(profil_destinatar) - 1] = '\0';
                                    xmlFree(profileAttr);
                                }
                            }
                            if (authAttr) xmlFree(authAttr);
                            xmlFree(nameAttr);
                            break;
                        }
                        if (nameAttr) xmlFree(nameAttr);
                    }
                }
                xmlFreeDoc(doc);
            }
            pthread_mutex_unlock(&db_mutex);

            if (!destinatar_autentificat) {
                snprintf(buffer, sizeof(buffer), "Eroare: Utilizatorul %s nu este autentificat sau nu există.\n", destinatar);
            } else {
                int poate_trimitere = 0;
                if (strcmp(profil_destinatar, "public") == 0) {
                    poate_trimitere = 1;
                } else if (strcmp(profil_destinatar, "privat") == 0) {
                    if (is_friend(destinatar, nume)) {
                        poate_trimitere = 1;
                    }
                }
                if (poate_trimitere) {
                    send_private_message(nume, destinatar, text_mesaj);
                    snprintf(buffer, sizeof(buffer), "[Server] Mesaj trimis către %s.\n", destinatar);
                } else {
                    snprintf(buffer, sizeof(buffer), "Eroare: Nu aveți permisiunea de a trimite mesaje către %s.\n", destinatar);
                }
            }
        }
    }
    send(client_socket, buffer, strlen(buffer), 0);
}

        else if (strcmp(comanda, "AdaugarePostare") == 0) {
            char postare_profil[10];
            char text_postare[256];
            if (sscanf(buffer, "AdaugarePostare %s %[^\n]", postare_profil, text_postare) != 2) 
            {
                strcpy(buffer, "Format: AdaugarePostare <public/privat> <text_postare>\n");
            } 
            else {
                if (strcmp(postare_profil, "privat") == 0) {
                    if (!autentificat) {
                        strcpy(buffer, "Trebuie să vă autentificați pentru o postare privată.\n");
                    } else {
                        pthread_mutex_lock(&db_mutex);
                        char msg[512];
                        snprintf(msg, sizeof(msg), "Postare [privat]: %s", text_postare);
                        add_user_event("users.xml", nume, tip, profil, msg, "post");
                        pthread_mutex_unlock(&db_mutex);
                        snprintf(buffer, sizeof(buffer), "[Server] Postare privată adăugată: %s\n", text_postare);
                    }
                } 
                else if (strcmp(postare_profil, "public") == 0) {
                    pthread_mutex_lock(&db_mutex);
                    char msg[512];
                    snprintf(msg, sizeof(msg), "Postare [public]: %s", text_postare);
                    const char* actualUser = autentificat ? nume    : "anon";
                    const char* actualTip  = autentificat ? tip     : "guest";
                    const char* actualProf = autentificat ? profil  : "public";
                    add_user_event("users.xml", actualUser, actualTip, actualProf, msg, "post");
                    pthread_mutex_unlock(&db_mutex);
                    snprintf(buffer, sizeof(buffer), "[Server] Postare publică adăugată: %s\n", text_postare);
                }
                else {
                    strcpy(buffer, "Profil invalid! Folosiți 'public' sau 'privat'.\n");
                }
            }
            send(client_socket, buffer, strlen(buffer), 0);
        }
        else if (strcmp(comanda, "AdaugarePrieten") == 0) {
            if (!autentificat) {
                strcpy(buffer, "Trebuie să vă autentificați mai întâi.\n");
            } else {
                char friend_name[50], friend_type[50];
                if (sscanf(buffer, "AdaugarePrieten %s %s", friend_name, friend_type) != 2) {
                    strcpy(buffer, "Format: AdaugarePrieten <nume_prieten> <tip_prietenie>\n");
                } else if (strcmp(friend_type, "close") != 0 && strcmp(friend_type, "friends") != 0) {
                    strcpy(buffer, "Tip prieten invalid! Folosiți 'close' sau 'friends'.\n");
                } else {
                    pthread_mutex_lock(&db_mutex);
                    xmlDocPtr doc = xmlParseFile("users.xml");
                    if (doc) {
                        xmlNodePtr root = xmlDocGetRootElement(doc);
                        xmlNodePtr friendNode = NULL;
                        for (xmlNodePtr node = root->children; node; node = node->next) {
                            if (node->type == XML_ELEMENT_NODE && xmlStrcmp(node->name, (const xmlChar *)"user") == 0) {
                                xmlChar *nameAttr = xmlGetProp(node, (const xmlChar *)"name");
                                xmlChar *authAttr = xmlGetProp(node, (const xmlChar *)"authenticated");
                                if (nameAttr && strcmp((const char *)nameAttr, friend_name) == 0 &&
                                    authAttr && strcmp((const char *)authAttr, "true") == 0) {
                                    friendNode = node;
                                }
                                xmlFree(nameAttr);
                                xmlFree(authAttr);
                            }
                        }
                        if (friendNode) {
                            add_friend_xml("users.xml", nume, tip, profil, friend_name, friend_type);
                            snprintf(buffer, sizeof(buffer), "[Server] Prieten adăugat: %s (%s)\n", friend_name, friend_type);
                        } else {
                            snprintf(buffer, sizeof(buffer), "Eroare: Utilizatorul %s nu este autentificat.\n", friend_name);
                        }
                        xmlFreeDoc(doc);
                    }
                    pthread_mutex_unlock(&db_mutex);
                }
            }
            send(client_socket, buffer, strlen(buffer), 0);
        }
        else if (strcmp(comanda, "AdaugareStire") == 0) {
    if (!autentificat) {
        strcpy(buffer, "Trebuie să vă autentificați mai întâi.\n");
    } else {
        char destinatar[10];
        char text_stire[256];
        if (sscanf(buffer, "AdaugareStire %s %[^\n]", destinatar, text_stire) != 2) {
            strcpy(buffer, "Format: AdaugareStire <public/friends/close> <text_stire>\n");
        } else if (strcmp(destinatar, "public") != 0 &&
                   strcmp(destinatar, "friends") != 0 &&
                   strcmp(destinatar, "close") != 0) {
            strcpy(buffer, "Destinatar invalid! Folosiți 'public', 'friends' sau 'close'.\n");
        } else {
            pthread_mutex_lock(&db_mutex);
            xmlDocPtr doc = xmlParseFile("users.xml");
            if (doc) {
                char msg[512];
                snprintf(msg, sizeof(msg), "Stire de la %s: %s\n", nume, text_stire);
                
                if (strcmp(destinatar, "public") == 0) {
                    add_stire_xml("users.xml", nume, tip, profil, "public", text_stire);
                    send_notification_to_all(msg, client_socket);  
                     }
                else if (strcmp(destinatar, "friends") == 0) {
                    add_stire_xml("users.xml", nume, tip, profil, "friends", text_stire);
                    send_notification_to_friends(nume, msg);
                }
                else if (strcmp(destinatar, "close") == 0) {
                    add_stire_xml("users.xml", nume, tip, profil, "close", text_stire);
                    send_notification_to_close_friends(nume, msg);
                }
                
                pthread_mutex_unlock(&db_mutex);
                snprintf(buffer, sizeof(buffer), "[Server] Știrea a fost trimisă către %s: %s\n", destinatar, text_stire);
                xmlFreeDoc(doc);
            } else {
                strcpy(buffer, "Eroare: Nu s-a putut deschide fișierul XML.\n");
            }
            pthread_mutex_unlock(&db_mutex);
        }
    }
    send(client_socket, buffer, strlen(buffer), 0);
}



        else if (strcmp(comanda, "VizualizareProfil") == 0) {
            char target_user[50];
            if (!autentificat) {
                strcpy(buffer, "Trebuie să fiți autentificat pentru a vizualiza profiluri.\n");
            } else if (sscanf(buffer, "VizualizareProfil %s", target_user) != 1) {
                strcpy(buffer, "Format: VizualizareProfil <nume_utilizator>\n");
            } else {
                pthread_mutex_lock(&db_mutex);
                xmlDocPtr doc = xmlParseFile("users.xml");
                if (doc) {
                    xmlNodePtr root = xmlDocGetRootElement(doc);
                    xmlNodePtr targetNode = NULL;
                    int is_friend = 0;
                    int is_public = 0;

                    for (xmlNodePtr node = root->children; node; node = node->next) {
                        if (node->type == XML_ELEMENT_NODE && xmlStrcmp(node->name, (const xmlChar *)"user") == 0) {
                            xmlChar *nameAttr = xmlGetProp(node, (const xmlChar *)"name");
                            xmlChar *profileAttr = xmlGetProp(node, (const xmlChar *)"profile");
                            if (nameAttr && strcmp((const char *)nameAttr, target_user) == 0) {
                                targetNode = node;
                                if (profileAttr && strcmp((const char *)profileAttr, "public") == 0) {
                                    is_public = 1;
                                }
                                xmlNodePtr friendsNode = NULL;
                                for (xmlNodePtr child = targetNode->children; child; child = child->next) {
                                    if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"friends") == 0) {
                                        friendsNode = child;
                                        break;
                                    }
                                }
                                if (friendsNode) {
                                    for (xmlNodePtr friendNode = friendsNode->children; friendNode; friendNode = friendNode->next) {
                                        if (friendNode->type == XML_ELEMENT_NODE && xmlStrcmp(friendNode->name, (const xmlChar *)"friend") == 0) {
                                            xmlChar *friendName = xmlGetProp(friendNode, (const xmlChar *)"name");
                                            if (friendName && strcmp((const char *)friendName, nume) == 0) {
                                                is_friend = 1;
                                            }
                                            xmlFree(friendName);
                                        }
                                    }
                                }
                            }
                            xmlFree(nameAttr);
                            xmlFree(profileAttr);
                        }
                    }

                    if (!targetNode) {
                        snprintf(buffer, sizeof(buffer), "Utilizatorul %s nu există.\n", target_user);
                    } else if (!is_public && !is_friend) {
                        snprintf(buffer, sizeof(buffer), "Profilul utilizatorului %s este privat.\n", target_user);
                    } else {
                        char response[BUFFER_SIZE * 2] = "";
                        snprintf(response, sizeof(response), "Profilul utilizatorului %s:\n", target_user);
                        strcat(response, "Prieteni:\n");
                        for (xmlNodePtr child = targetNode->children; child; child = child->next) {
                            if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"friends") == 0) {
                                for (xmlNodePtr friendNode = child->children; friendNode; friendNode = friendNode->next) {
                                    if (friendNode->type == XML_ELEMENT_NODE && xmlStrcmp(friendNode->name, (const xmlChar *)"friend") == 0) {
                                        xmlChar *friendName = xmlGetProp(friendNode, (const xmlChar *)"name");
                                        if (friendName) {
                                            snprintf(response + strlen(response), sizeof(response) - strlen(response), "- %s\n", friendName);
                                            xmlFree(friendName);
                                        }
                                    }
                                }
                            }
                        }
                        strcat(response, "Postări:\n");
                        for (xmlNodePtr child = targetNode->children; child; child = child->next) {
                            if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"events") == 0) {
                                for (xmlNodePtr eventNode = child->children; eventNode; eventNode = eventNode->next) {
                                    if (eventNode->type == XML_ELEMENT_NODE && xmlStrcmp(eventNode->name, (const xmlChar *)"event") == 0) {
                                        xmlChar *typeAttr = xmlGetProp(eventNode, (const xmlChar *)"type");
                                        xmlChar *content = xmlNodeGetContent(eventNode);


                                        if (typeAttr && strcmp((const char *)typeAttr, "post") == 0) {
                                            if (strstr((const char *)content, "[public]") != NULL) {
                                                snprintf(response + strlen(response), sizeof(response) - strlen(response),
                                                         "- [Public]: %s\n", content);
                                            } else if (is_friend && strstr((const char *)content, "[privat]") != NULL) {
                                                snprintf(response + strlen(response), sizeof(response) - strlen(response),
                                                         "- [Privat]: %s\n", content);
                                            }
                                        }
                                        xmlFree(typeAttr);
                                        xmlFree(content);
                                    }
                                }
                            }
                        }
                        strncpy(buffer, response, BUFFER_SIZE);
                    }

                    xmlFreeDoc(doc);
                } else {
                    snprintf(buffer, sizeof(buffer), "Eroare: Nu s-a putut deschide fișierul XML.\n");
                }
                pthread_mutex_unlock(&db_mutex);
            }
            send(client_socket, buffer, strlen(buffer), 0);
        }
        else if (strcmp(comanda, "VizualizarePostariPublice") == 0) {
            pthread_mutex_lock(&db_mutex);
            xmlDocPtr doc = xmlParseFile("users.xml");
            if (doc) {
                xmlNodePtr root = xmlDocGetRootElement(doc);
                char response[BUFFER_SIZE * 2] = "Postări publice:\n";
                for (xmlNodePtr userNode = root->children; userNode; userNode = userNode->next) {
                    if (userNode->type == XML_ELEMENT_NODE && xmlStrcmp(userNode->name, (const xmlChar *)"user") == 0) {
                        xmlChar *username = xmlGetProp(userNode, (const xmlChar *)"name");
                        for (xmlNodePtr child = userNode->children; child; child = child->next) {
                            if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *)"events") == 0) {
                                for (xmlNodePtr eventNode = child->children; eventNode; eventNode = eventNode->next) {
                                    if (eventNode->type == XML_ELEMENT_NODE && xmlStrcmp(eventNode->name, (const xmlChar *)"event") == 0) {
                                        xmlChar *typeAttr = xmlGetProp(eventNode, (const xmlChar *)"type");
                                        xmlChar *content = xmlNodeGetContent(eventNode);
                                        if (typeAttr && strcmp((const char *)typeAttr, "post") == 0 &&
                                            content && strstr((const char *)content, "[public]") != NULL) {
                                            snprintf(response + strlen(response), sizeof(response) - strlen(response),
                                                     "- [%s]: %s\n", username ? (const char *)username : "Anonim", content);
                                        }

                                        if (typeAttr) xmlFree(typeAttr);
                                        if (content) xmlFree(content);
                                    }
                                }
                            }
                        }
                        if (username) xmlFree(username);
                    }
                }

                if (strlen(response) == strlen("Postări publice:\n")) {
                    strcat(response, "Nu există postări publice.\n");
                }

                strncpy(buffer, response, BUFFER_SIZE);
                xmlFreeDoc(doc);
            } else {
                snprintf(buffer, sizeof(buffer), "Eroare: Nu s-a putut deschide fișierul XML.\n");
            }
            pthread_mutex_unlock(&db_mutex);
            send(client_socket, buffer, strlen(buffer), 0);
        }
        else if (strcmp(comanda, "SetareProfil") == 0) {
            if (!autentificat) {
                strcpy(buffer, "Trebuie să vă autentificați mai întâi.\n");
            } else {
                char newProfile[50];
                if (sscanf(buffer, "SetareProfil %s", newProfile) != 1) {
                    strcpy(buffer, "Format: SetareProfil <public/privat>\n");
                } else {
                    if (strcmp(newProfile, "public") != 0 && strcmp(newProfile, "privat") != 0) {
                        strcpy(buffer, "Profil invalid. Folosiți 'public' sau 'privat'.\n");
                    } else {
                        pthread_mutex_lock(&db_mutex);
                        xmlDocPtr doc = xmlParseFile("users.xml");
                        if (doc) {
                            xmlNodePtr userNode = get_or_create_user(doc, nume, tip, profil);
                            if (userNode) {
                                xmlSetProp(userNode, BAD_CAST "profile", BAD_CAST newProfile);
                                write_xml(doc, "users.xml");
                                strcpy(profil, newProfile); 
                                snprintf(buffer, sizeof(buffer), "[Server] Profil actualizat la: %s.\n", newProfile);
                            } else {
                                strcpy(buffer, "Eroare: Utilizatorul nu a fost găsit în fișier.\n");
                            }
                            xmlFreeDoc(doc);
                        } else {
                            strcpy(buffer, "Eroare: Nu s-a putut deschide fișierul XML.\n");
                        }
                        pthread_mutex_unlock(&db_mutex);
                    }
                }
            }
            send(client_socket, buffer, strlen(buffer), 0);
        }
        else if (strcmp(comanda, "Deconectare") == 0) {
    if (autentificat) {
        pthread_mutex_lock(&db_mutex);
        xmlDocPtr doc = xmlParseFile("users.xml");
        if (doc) {
            xmlNodePtr userNode = get_or_create_user(doc, nume, tip, profil);
            if (userNode) {
                xmlUnsetProp(userNode, BAD_CAST "authenticated");
                write_xml(doc, "users.xml");
            }
            xmlFreeDoc(doc);
        }
        pthread_mutex_unlock(&db_mutex);
    }
    remove_client(client_socket);
    strcpy(buffer, "[Server]: Deconectare de la server.\n");
    send(client_socket, buffer, strlen(buffer), 0);

    close(client_socket);
    break;
}


        else {
            strcpy(buffer,
                   "Comandă necunoscută. Comenzi disponibile:\n"
                   "  Autentificare <nume> <tip> <public/privat>\n"
                   "  SetareProfil <public/privat>\n"
                   "  VizualizareProfil <nume> \n"
                   "  VizualizarePostariPublice \n"
                   "  AdaugarePrieten <nume_prieten> <tip_prietenie>\n"
                   "  AdaugareStire <destinatar> <text_stire>\n"
                   "  AdaugarePostare <public/privat> <text_postare>\n"
                   "  MesajPrivat <nume> <text_mesaj>\n"
                   "  Deconectare\n");
            send(client_socket, buffer, strlen(buffer), 0);
        }
    }

    return NULL;
}

int server_stop = 0;

int main() {

    xmlKeepBlanksDefault(0);
    xmlInitParser();
    LIBXML_TEST_VERSION
    xmlIndentTreeOutput = 1;
    pthread_mutex_init(&db_mutex, NULL);
    initialize_xml_file("users.xml");
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Eroare la crearea socket-ului server");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Eroare la bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, 5) == -1) {
        perror("Eroare la listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("[Server] Rulând pe portul %d...\n", PORT);
    while (!server_stop) {
        int client_sock = accept(server_socket,(struct sockaddr*)&client_addr,&client_addr_len);
        if (client_sock == -1) {
            perror("Eroare la accept");
            continue;
        }
        printf("[Server] Client conectat.\n");
        pthread_t thread_id;
        int *arg = malloc(sizeof(int));
        *arg = client_sock;
        if (pthread_create(&thread_id, NULL, handle_client, arg) != 0) {
            perror("Eroare la crearea thread-ului");
            free(arg);
            close(client_sock);
        }
        pthread_detach(thread_id);
    }
    close(server_socket);
    pthread_mutex_destroy(&db_mutex);
    xmlCleanupParser();
    xmlMemoryDump();
    printf("[Server] Oprit.\n");
    return 0;
}