function escapeHTML(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#39;");
}

async function handleAuth() {
  const usernameInput = document.getElementById("username");
  const passwordInput = document.getElementById("password");
  const modeInput = document.getElementById("mode");

  const username = usernameInput?.value.trim();
  const password = passwordInput?.value;
  const mode = modeInput?.value;

  const msgBox = document.getElementById("authMsg");

  if (!username || !password) {
    msgBox.textContent = "Completează toate câmpurile.";
    return;
  }

  try {
    const response = await fetch(`/api/auth/${encodeURIComponent(mode)}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        username: escapeHTML(username),
        password: escapeHTML(password)
      })
    });

    const result = await response.json();

    if (!result.success) {
      msgBox.textContent = escapeHTML(result.message);
    } else {
      sessionStorage.setItem("username", escapeHTML(username));
      sessionStorage.setItem("role", escapeHTML(result.user?.role || "user"));
      window.location.href = "index.html"; // sau transform.html
    }
  } catch (err) {
    msgBox.textContent = "Eroare de rețea sau server.";
    console.error("Autentificare eșuată:", err);
  }
}
function showLoginStatus() {
  const user = sessionStorage.getItem("username");
  const role = sessionStorage.getItem("role");
  const statusBox = document.getElementById("loginStatus");

  if (user) {
    statusBox.innerHTML = `
      👋 Conectat ca <strong>${escapeHTML(user)}</strong> (${escapeHTML(role)})
      <button onclick="logout()" style="margin-left:10px;">Ieșire</button>
    `;
    document.querySelector(".auth-box")?.remove(); // ascunde formularul
  } else if (role === "admin") {
  statusBox.innerHTML += `<a href="admin.html" style="margin-left: 10px;">⚙️ Admin</a>`;
}
 
  else {
    statusBox.innerHTML = "🔐 Nu ești conectat(ă).";
  }
}

function logout() {
  sessionStorage.removeItem("username");
  sessionStorage.removeItem("role");
  location.reload();
}

// ✅ rulează când pagina e gata
window.addEventListener("DOMContentLoaded", showLoginStatus);
