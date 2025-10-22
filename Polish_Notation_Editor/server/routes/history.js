const express = require('express');
const fs = require('fs');
const path = require('path');
const router = express.Router();

const DATA_DIR = path.join(__dirname, '..', 'data');

// Load history
router.get('/:username', (req, res) => {
  const username = req.params.username;
  const filePath = path.join(DATA_DIR, `${username}.json`);
  if (fs.existsSync(filePath)) {
    const data = JSON.parse(fs.readFileSync(filePath, 'utf-8'));
    res.json(data);
  } else {
    res.json({ expressions: [] }); // nou user = gol
  }
});

// Save history
router.post('/:username', (req, res) => {
  const username = req.params.username;
  const filePath = path.join(DATA_DIR, `${username}.json`);
  const data = req.body; // { expressions: [...] }
  fs.writeFileSync(filePath, JSON.stringify(data, null, 2));
  res.json({ success: true });
});

module.exports = router;
