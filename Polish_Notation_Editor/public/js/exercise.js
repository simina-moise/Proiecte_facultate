let exerciseList = [];
let expressionHistory = [];
let favoriteExpressions = [];
let score = 0;
let maxScore = 0;
let progressByExercise = [];
let currentExerciseIndex = 0;
let hintUsedByExercise = [];
let attemptedByExercise = [];
let timerIntervalId = null;
let timerTimeoutId = null;

// la începutul fișierului sau la nivel de modul
function clearExistingTimer() {
  clearInterval(timerIntervalId);
  clearTimeout(timerTimeoutId);
  document.getElementById("timerDisplay")?.remove();
}

function startTimer(seconds) {
  clearExistingTimer();
  const display = document.createElement("div");
  display.id = "timerDisplay";
  display.style = "text-align:center; font-size:1.2em; margin-bottom:10px; color:#d9534f;";
  document.querySelector(".exercise-box").prepend(display);

  let remaining = seconds;
  display.textContent = `⏱️ Time left: ${remaining}s`;

  // actualizează textul la fiecare secundă
  timerIntervalId = setInterval(() => {
    remaining--;
    display.textContent = `⏱️ Time left: ${remaining}s`;
  }, 1000);

  // când expiră timpul
  timerTimeoutId = setTimeout(() => {
    clearExistingTimer();
    // marchează exercițiul ca încercat
    attemptedByExercise[currentExerciseIndex] = true;
    progressByExercise[currentExerciseIndex] = 0;
    // actualizează scorul total și UI
    document.getElementById("feedback").textContent = "⏰ Timp expirat! Punctaj: 0";
    document.getElementById("progress").textContent =
      `Scor: ${score}/${maxScore} | Exerciții rezolvate: ${progressByExercise.filter(p => p>0).length}/${exerciseList.length}`;
    // disable inputs
    document.getElementById("prefixInput").disabled = true;
    document.getElementById("postfixInput").disabled = true;
    document.getElementById("checkBtn").disabled = true;
    document.getElementById("hintBtn").disabled = true;
    // salvează progresul cu 0 puncte
    saveUserProgress();
    loadLeaderboard();
  }, seconds * 1000);
}


async function loadExercises() {
  const res = await fetch("/api/exercises");
  const data = await res.json();
  exerciseList = data;

  // Inițializare scor
  score = 0;
  maxScore = exerciseList.length * 2;
  progressByExercise = Array(exerciseList.length).fill(0);
  currentExerciseIndex = 0;
hintUsedByExercise      = Array(exerciseList.length).fill(false); // dacă ai deja hint-logic

attemptedByExercise     = Array(exerciseList.length).fill(false);
  const btnContainer = document.getElementById("exerciseButtons");
  btnContainer.innerHTML = "";
  for (let i = 0; i < exerciseList.length; i++) {
    const btn = document.createElement("button");
    btn.textContent = `Exercițiul ${i + 1}`;
    btn.onclick = () => showExercise(i);
    btnContainer.appendChild(btn);
  }

  showExercise(0);

  const role = sessionStorage.getItem("role");
  if (role === "admin") {
    document.getElementById("adminActions").style.display = "block";
    document.getElementById("userActions").style.display = "none";
    document.getElementById("feedback").style.display = "none";
    document.getElementById("progress").style.display = "none";
    document.getElementById("hintSvgWrapper").style.display = "none";
  }
}

function showExercise(index) {
  const ex = exerciseList[index];
  currentExerciseIndex = index;

  const isAdmin = sessionStorage.getItem("role") === "admin";
  clearExistingTimer();
  if (!isAdmin && ex.timeLimit && ex.timeLimit > 0) {
    startTimer(ex.timeLimit);
  }
  const exInfixContainer = document.getElementById("exInfix");

  if (isAdmin) {
    exInfixContainer.innerHTML = `<input id="editInfix" value="${ex.infix}" style="width: 90%;">`;
    document.getElementById("prefixInput").value = ex.prefix;
    document.getElementById("postfixInput").value = ex.postfix;
    document.getElementById("timerInput").value = ex.timeLimit || "";
  } else {
    exInfixContainer.textContent = ex.infix;
    document.getElementById("prefixInput").value = "";
    document.getElementById("postfixInput").value = "";
  }

  document.getElementById("feedback").textContent = "";
  document.getElementById("progress").textContent = `Scor: ${score}/${maxScore}`;
  document.getElementById("hintSvgWrapper").style.display = "none";
  // la sfârșitul showExercise:
const tried = attemptedByExercise[index];
document.getElementById("prefixInput").disabled  = tried;
document.getElementById("postfixInput").disabled = tried;
document.getElementById("checkBtn").disabled     = tried;
document.getElementById("hintBtn").disabled      = tried;

if (tried) {
  document.getElementById("feedback").textContent =
    "🎉 Ai încercat deja acest exercițiu și nu poți reîncerca.";
}

}

async function checkExercise() {
  clearExistingTimer();
  const userPrefix = document.getElementById("prefixInput").value.trim();
  const userPostfix = document.getElementById("postfixInput").value.trim();
  const ex = exerciseList[currentExerciseIndex];
  const fb = [];
  let newPoints = 0;

  if (userPrefix === ex.prefix) {
    fb.push("✅ Prefix corect");
    newPoints += 1;
  } else {
    fb.push(`❌ Prefix greșit: ai scris "${userPrefix}", trebuia "${ex.prefix}"`);
  }

  if (userPostfix === ex.postfix) {
    fb.push("✅ Postfix corect");
    newPoints += 1;
  } else {
    fb.push(`❌ Postfix greșit: ai scris "${userPostfix}", trebuia "${ex.postfix}"`);
  }
 // ⚠️ penalizare hint: dacă hintUsed, reduci newPoints la jumate
 if (hintUsedByExercise[currentExerciseIndex]) {
   fb.unshift("⚠️ Ai folosit hint; punctaj redus la jumătate");
   newPoints = newPoints / 2;
 }
 if (attemptedByExercise[currentExerciseIndex]) {
    document.getElementById("feedback").textContent =
      "⚠️ Nu poți reîncerca acest exercițiu.";
    return;
  }
  const previousPoints = progressByExercise[currentExerciseIndex];
  if (newPoints > previousPoints) {
    score += (newPoints - previousPoints);
    progressByExercise[currentExerciseIndex] = newPoints;
  }
    attemptedByExercise[currentExerciseIndex] = true;

  document.getElementById("feedback").textContent = fb.join(" | ");
  document.getElementById("progress").textContent = `Scor: ${score.toFixed(1)}/${maxScore} | Exerciții rezolvate: ${progressByExercise.filter(p => p > 0).length}/${exerciseList.length}`;

  await saveUserProgress();
  await loadLeaderboard();
}

function resetScore() {
  score = 0;
  progressByExercise = Array(exerciseList.length).fill(0);
  document.getElementById("progress").textContent = `Scor: 0/${maxScore}`;
  document.getElementById("feedback").textContent = "";
}

async function saveUserProgress() {
  const username = sessionStorage.getItem("username");
  if (!username) return;

  const history = expressionHistory || [];
  const favorites = favoriteExpressions || [];

  const payload = {
    username,
    score,
    history,
    favorites,
  };

  console.log("🟢 Trimit progres (fixat):", payload);

  await fetch("/api/auth/update", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(payload), // ✅ AICI ERA BUGUL!
  });
}




async function loadLeaderboard() {
  try {
    const res = await fetch("/api/leaderboard");
    const data = await res.json();

    const list = document.getElementById("leaderboardList");
    if (!list) return;

    list.innerHTML = "";
    data.forEach(user => {
      const li = document.createElement("li");
      li.textContent = `${user.username} — ${user.score} puncte`;
      list.appendChild(li);
    });
  } catch (err) {
    console.error("❌ Eroare la încărcarea clasamentului:", err);
  }
}

async function saveExercisesToBackend() {
  const isAdmin = sessionStorage.getItem("role") === "admin";
  if (!isAdmin) return;

  const index = currentExerciseIndex;
  const infix = document.getElementById("editInfix")?.value.trim();
  const prefix = document.getElementById("prefixInput")?.value.trim();
  const postfix = document.getElementById("postfixInput")?.value.trim();
  const timeLimit = parseInt(document.getElementById("timerInput").value, 10) || 0;

exerciseList[index] = { infix, prefix, postfix, timeLimit };

  try {
    const res = await fetch("/api/admin/exercises", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ exercises: exerciseList })
    });
    const result = await res.json();
    alert(result.message || "✅ Salvat cu succes");
  } catch (err) {
    alert("❌ Eroare la salvare");
  }
}
// după loadExercises(); loadLeaderboard();
document.getElementById("hintBtn").addEventListener("click", () => {
  // marchează că s-a folosit hint pentru exercițiul curent:
  hintUsedByExercise[currentExerciseIndex] = true;
  // apoi afișează arborele (funcția ta existentă):
  showHintTree();
});

// apelare la încărcare
loadExercises();
loadLeaderboard();
