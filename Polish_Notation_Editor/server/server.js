const http = require('http');
const fs = require('fs');
const path = require('path');
const url = require('url');

const usersPath = './server/data/users.json';
const historyDir = './server/data';
const staticDir = path.join(__dirname, '../public');

function parseBody(req) {
  return new Promise((resolve, reject) => {
    let body = '';
    req.on('data', chunk => (body += chunk.toString()));
    req.on('end', () => {
      try {
        resolve(JSON.parse(body));
      } catch (e) {
        reject(e);
      }
    });
  });
}

function sendJson(res, data, status = 200) {
  if (!res.headersSent) {
    res.writeHead(status, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify(data));
  }
}

const server = http.createServer(async (req, res) => {
  const parsedUrl = url.parse(req.url, true);
  const pathname = parsedUrl.pathname;
  const method = req.method;

  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS');
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
  if (method === 'OPTIONS') return res.end();

  const filePath = path.join(staticDir, pathname === '/' ? 'index.html' : pathname);
  if (fs.existsSync(filePath) && fs.statSync(filePath).isFile()) {
    const ext = path.extname(filePath).toLowerCase();
    const contentType = {
      '.html': 'text/html',
      '.css': 'text/css',
      '.js': 'application/javascript',
      '.json': 'application/json',
      '.svg': 'image/svg+xml',
      '.png': 'image/png',
      '.jpg': 'image/jpeg',
      '.ico': 'image/x-icon'
    }[ext] || 'application/octet-stream';

    res.writeHead(200, { 'Content-Type': contentType });
    return res.end(fs.readFileSync(filePath));
  }
if (method === 'POST' && pathname === '/api/auth/update') {
  try {
    const contentType = req.headers['content-type'];
    if (contentType !== 'application/json') {
      return sendJson(res, { success: false, message: 'Content-Type invalid' }, 400);
    }

    const body = await parseBody(req);

    if (!body || typeof body.username !== 'string') {
      return sendJson(res, { success: false, message: 'Date lipsă sau invalide' }, 400);
    }

    const { username, score, history, favorites } = body;
    //console.log("🟢 UPDATE primit de la client:", body);

    const users = fs.existsSync(usersPath)
      ? JSON.parse(fs.readFileSync(usersPath))
      : [];

    const user = users.find(u => u.username === username);
    if (!user) {
      return sendJson(res, { success: false, message: 'Utilizator inexistent' }, 404);
    }

    user.score = Number(score);
    if (Array.isArray(history)) user.history = history;
    if (Array.isArray(favorites)) user.favorites = favorites;

    fs.writeFileSync(usersPath, JSON.stringify(users, null, 2));

    const userFile = path.join(historyDir, `${username}.json`);
    const userData = { score, expressions: history || [], favorites: favorites || [] };
    fs.writeFileSync(userFile, JSON.stringify(userData, null, 2));

    return sendJson(res, { success: true });
  } catch (err) {
    console.error("❌ Eroare server la update:", err);
    return sendJson(res, { success: false, message: 'Eroare internă' }, 500);
  }
}
  if (method === 'POST' && pathname.startsWith('/api/auth/')) {
    const mode = pathname.split('/').pop();
    try {
      const { username, password } = await parseBody(req);
      if (!username || !password)
        return sendJson(res, { success: false, message: 'Date lipsă' }, 400);

      const users = fs.existsSync(usersPath)
        ? JSON.parse(fs.readFileSync(usersPath))
        : [];

      if (mode === 'register') {
        if (users.some(u => u.username === username))
          return sendJson(res, { success: false, message: 'Utilizator deja existent' });
        const newUser = { username, password, role: 'user', score: 0 };
        users.push(newUser);
fs.writeFileSync(usersPath, JSON.stringify(users, null, 2));

// Dacă vrei să salvezi și scorul individual per fișier user (opțional)
const userFile = path.join(historyDir, `${username}.json`);
let userData = {};
if (fs.existsSync(userFile)) {
  userData = JSON.parse(fs.readFileSync(userFile));
}
userData.score = 0;
userData.expressions = [];
  userData.favorites = [];
fs.writeFileSync(userFile, JSON.stringify(userData, null, 2));
        return sendJson(res, { success: true, user: newUser });
      }

      if (mode === 'login') {
        const user = users.find(u => u.username === username && u.password === password);
        if (!user)
          return sendJson(res, { success: false, message: 'Autentificare eșuată' });
        return sendJson(res, { success: true, user });
      }

      return sendJson(res, { success: false, message: 'Rută invalidă' }, 404);
    } catch {
      return sendJson(res, { success: false, message: 'Eroare server' }, 500);
    }
  }


  if (method === 'GET' && pathname.startsWith('/api/history/')) {
    const username = pathname.split('/').pop();
    const file = path.join(historyDir, `${username}.json`);
    if (fs.existsSync(file)) {
      try {
        const content = fs.readFileSync(file, 'utf-8');
        const parsed = JSON.parse(content);
        return sendJson(res, { success: true, expressions: parsed.expressions || [] });
      } catch {
        return sendJson(res, { success: false, message: 'Eroare la citire' });
      }
    } else {
      return sendJson(res, { success: true, expressions: [] });
    }
  }

  if (method === 'POST' && pathname.startsWith('/api/history/')) {
    const username = pathname.split('/').pop();
    const file = path.join(historyDir, `${username}.json`);
    try {
      const data = await parseBody(req);
      fs.writeFileSync(file, JSON.stringify(data, null, 2));
      return sendJson(res, { success: true });
    } catch {
      return sendJson(res, { success: false, message: 'Eroare la salvare' }, 500);
    }
  }

  if (method === 'GET' && pathname === '/api/exercises') {
    const file = path.join(__dirname, 'data', 'exercises.json');
    if (fs.existsSync(file)) {
      const content = fs.readFileSync(file, 'utf-8');
      return sendJson(res, JSON.parse(content));
    } else {
      return sendJson(res, []);
    }
  }

  if (method === 'POST' && pathname === '/api/admin/exercises') {
    try {
      const { exercises } = await parseBody(req);
      const file = path.join(__dirname, 'data', 'exercises.json');
      fs.writeFileSync(file, JSON.stringify(exercises, null, 2));
      return sendJson(res, { success: true, message: 'Exercițiile au fost salvate' });
    } catch {
      return sendJson(res, { success: false, message: 'Eroare la salvare' }, 500);
    }
  }

  if (method === 'GET' && pathname === '/api/leaderboard') {
    const file = path.join(__dirname, 'data', 'users.json');
    fs.readFile(file, 'utf-8', (err, data) => {
      if (err) {
        return sendJson(res, { success: false, message: 'Eroare la citirea clasamentului' }, 500);
      }
      const users = JSON.parse(data);
      const leaderboard = users
        .filter(u => u.role === 'user')
        .map(u => ({ username: u.username, score: u.score || 0 }))
        .sort((a, b) => b.score - a.score)
        .slice(0, 10);

      return sendJson(res, leaderboard);
    });
    return;
  }



  return sendJson(res, { success: false, message: 'Rută necunoscută' }, 404);
});

server.listen(3000, () => {
  console.log('✅ Server pornit pe http://localhost:3000');
});