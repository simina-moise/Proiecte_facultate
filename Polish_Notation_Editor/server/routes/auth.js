const express = require("express");
const router = express.Router();
const {
  loadUsers,
  saveUsers,
  findUser,
  updateUserData
} = require("../models/userData");

router.post("/login", (req, res) => {
  const { username, password } = req.body;
  const user = findUser(username);

  if (!user || user.password !== password) {
    return res.status(401).json({ success: false, message: "Credențiale greșite" });
  }

  res.json({ success: true, user });
});

router.post("/register", (req, res) => {
  const { username, password } = req.body;
  const users = loadUsers();

  if (users.find(u => u.username === username)) {
    return res.status(400).json({ success: false, message: "Utilizator existent" });
  }

  const newUser = {
    username,
    password,
    role: "user",
    score: 0,
    history: [],
    favorites: []
  };

  users.push(newUser);
  saveUsers(users);
  res.json({ success: true });
});

router.post("/update", (req, res) => {
  const { username, score, history, favorites } = req.body;
  const ok = updateUserData(username, { score, history, favorites });

  if (ok) {
    res.json({ success: true });
  } else {
    res.status(404).json({ success: false, message: "Utilizator inexistent" });
  }
});

router.get("/all", (req, res) => {
  const users = loadUsers();
  const publicData = users.map(({ username, score, role }) => ({ username, score, role }));
  res.json(publicData);
});

module.exports = router;
