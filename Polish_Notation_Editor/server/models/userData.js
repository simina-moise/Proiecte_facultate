const fs = require("fs");
const path = require("path");

const USERS_FILE = path.join(__dirname, "../data/users.json");

function loadUsers() {
  if (!fs.existsSync(USERS_FILE)) return [];
  const content = fs.readFileSync(USERS_FILE, "utf-8");
  return JSON.parse(content || "[]");
}

function saveUsers(users) {
  fs.writeFileSync(USERS_FILE, JSON.stringify(users, null, 2));
}

function findUser(username) {
  const users = loadUsers();
  return users.find(u => u.username === username);
}

function updateUserData(username, newData) {
  const users = loadUsers();
  const index = users.findIndex(u => u.username === username);
  if (index !== -1) {
    users[index] = { ...users[index], ...newData };
    saveUsers(users);
    return true;
  }
  return false;
}

module.exports = {
  loadUsers,
  saveUsers,
  findUser,
  updateUserData,
};
