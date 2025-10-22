const prefixExamples = [
    { expr: "+ 1 2", comment: "" },
    { expr: "* + 1 2 3", comment: "" },
    { expr: "sqrt ^ 2 3", comment: "" },
    { expr: "log 100", comment: "" },
    { expr: "+ 1 * 2 pi", comment: "" },
  ];
  
  const postfixExamples = [
    { expr: "1 2 +", comment: "" },
    { expr: "1 2 + 3 *", comment: "" },
    { expr: "2 3 ^ sqrt", comment: "" },
    { expr: "100 log", comment: "" },
    { expr: "1 2 pi * +", comment: "" },
  ];
  
  let currentExampleIndex = null;
  let currentExpr = null; // expresia selectată curent (din listă sau din fișier)

  function displayExamples() {
    const list = document.getElementById("examplesList");
    list.innerHTML = "";
  
    examples.forEach((ex, index) => {
      const li = document.createElement("li");
      li.innerHTML = `
        <button onclick="loadExample(${index})">${ex.expr}</button>
        <span> ${ex.comment ? `📝 ${ex.comment}` : ""}</span>
      `;
      list.appendChild(li);
    });
  }
  
  function loadExample(index) {
    const expr = examples[index].expr;
    currentExpr = expr;
    document.getElementById("inputExpr").value = expr;
    if (document.title.includes("Postfix")) {
        evaluatePostfixExpr(false);
      } else {
        evaluatePrefixExpr(false);
      }
      
    currentExampleIndex = index;
    document.getElementById("comment").value = examples[index].comment || "";
  }
  
  async function loadUserHistory(username) {
  try {
    const res = await fetch(`/api/history/${username}`);
    const data = await res.json();
    HistoryModel.expressions = data.expressions || [];
    updateHistoryUI();
  } catch (err) {
    console.error("❌ Eroare la încărcarea istoricului:", err);
  }
}

function saveComment() {
  const newComment = document.getElementById("comment").value.trim();
  if (!currentExpr) return alert("⚠️ Nicio expresie selectată.");

  let found = false;

  for (let i = 0; i < HistoryModel.expressions.length; i++) {
    if (HistoryModel.expressions[i].expr === currentExpr) {
      HistoryModel.expressions[i].comment = newComment;
      found = true;
      break;
    }
  }

  if (!found) {
    HistoryModel.expressions.push({
      expr: currentExpr,
      comment: newComment
    });
  }

  const username = sessionStorage.getItem("username");
  if (username) {
    fetch(`/api/history/${username}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ expressions: HistoryModel.expressions })
    }).then(res => {
      console.log("✅ Comentariu salvat:", res.status);
    });
  }

  updateHistoryUI();
  document.getElementById("commentDisplay").textContent =
    `Comentariu salvat: ${newComment}`;
}




  
  let examples = [];

  window.onload = () => {
    const isPrefix = document.title.includes("Prefix");
    examples = isPrefix ? prefixExamples : postfixExamples;
const username = sessionStorage.getItem("username");
if (username) {
  loadUserHistory(username);
}
    displayExamples();
  };
  
  function saveExpressionToHistory(expr) {
    HistoryModel.add(expr);
    const username = sessionStorage.getItem("username");
if (username) {
  fetch(`/api/history/${username}`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ expressions: HistoryModel.expressions })
  });
}

    updateHistoryUI();
  }
  function deleteExpression(index) {
  if (!confirm("❗ Sigur vrei să ștergi această expresie?")) return;

  HistoryModel.expressions.splice(index, 1);
  syncHistoryWithServer();
  updateHistoryUI();
}
function deleteComment(index) {
  const entry = HistoryModel.expressions[index];

  if (typeof entry === "string") {
    alert("⚠️ Această expresie nu are comentariu.");
    return;
  }

  if (!confirm("❗ Sigur vrei să ștergi comentariul?")) return;

  entry.comment = "";
  HistoryModel.expressions[index] = entry;

  syncHistoryWithServer();
  updateHistoryUI();
}
function syncHistoryWithServer() {
  const username = sessionStorage.getItem("username");
  if (!username) return;

  fetch(`/api/history/${username}`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ expressions: HistoryModel.expressions })
  }).then(res => {
    console.log("✅ Istoric actualizat:", res.status);
  }).catch(err => {
    console.error("❌ Eroare backend:", err);
  });
}
function clearHistory() {
  if (!confirm("❗ Ești sigur că vrei să ștergi TOT istoricul?")) return;

  HistoryModel.expressions = [];
  syncHistoryWithServer();
  updateHistoryUI();
}


function updateHistoryUI() {
  const container = document.getElementById("historyList");
  container.innerHTML = "";

  HistoryModel.expressions.forEach((entry, i) => {
    const exprText = typeof entry === "string" ? entry : entry.expr;
    const commentText = typeof entry === "string" ? "" : entry.comment || "";

    const li = document.createElement("li");
    const shownExpr = exprText.replace(/\b3\.141592653589793\b/g, 'π');

    let html = `${i + 1}. ${shownExpr}`;
    if (commentText) {
      html += ` <span style="color: gray">📝 ${commentText}</span>`;
      html += ` <button onclick="deleteComment(${i})">❌ comentariu</button>`;
    }
    html += ` <button onclick="deleteExpression(${i})">🗑️</button>`;

    li.innerHTML = html;
    container.appendChild(li);
  });
}


  function exportHistoryJSON() {
    const data = HistoryModel.exportJSON();
    downloadFile("istoric.json", "application/json", data);
  }
  
  function exportHistoryXML() {
    const data = HistoryModel.exportXML();
    downloadFile("istoric.xml", "application/xml", data);
  }
  
  function downloadFile(filename, type, data) {
    const blob = new Blob([data], { type });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = filename;
    a.click();
    URL.revokeObjectURL(url);
  }
  function generateMathML(expr, containerId) {
  const tokens = expr.trim().split(/\s+/);

  function build(tokens) {
    if (tokens.length === 0) return "";

    const token = tokens.shift();

    if (!isNaN(token) || token === "π" || token === "e" || /^-?\d+(\.\d+)?$/.test(token)) {
  return `<mn>${token}</mn>`;
}

    if (["sqrt", "sin", "cos", "tan", "ln", "log", "abs", "neg", "exp", "floor", "ceil"].includes(token)) {
      const arg = build(tokens);
      switch (token) {
        case "sqrt": return `<msqrt>${arg}</msqrt>`;
        case "abs": return `<mrow><mo>|</mo>${arg}<mo>|</mo></mrow>`;
        case "neg": return `<mrow><mo>-</mo>${arg}</mrow>`;
        case "floor": return `<mrow><mo>⌊</mo>${arg}<mo>⌋</mo></mrow>`;
        case "ceil": return `<mrow><mo>⌈</mo>${arg}<mo>⌉</mo></mrow>`;
        default: return `<mrow><mi>${token}</mi><mo>(</mo>${arg}<mo>)</mo></mrow>`;
      }
    }

    const left = build(tokens);
    const right = build(tokens);

    switch (token) {
      case "^":
        return `<msup><mrow>${left}</mrow><mrow>${right}</mrow></msup>`;
      case "+": case "-": case "*": case "/":
        return `<mrow><mo>(</mo>${left}<mo> ${token} </mo>${right}<mo>)</mo></mrow>`;
      default:
        return `<mrow>${token} ${left} ${right}</mrow>`;
    }
  }

  const mathML = `<math xmlns="http://www.w3.org/1998/Math/MathML">${build([...tokens])}</math>`;
  const container = document.getElementById(containerId);
  container.innerHTML = mathML;

  if (window.MathJax && window.MathJax.typesetPromise) {
    MathJax.typesetClear(); // curăță înainte
    MathJax.typesetPromise([container]);
  }
}
function generateMathMLPostfix(expr, containerId) {
  const tokens = expr.trim().split(/\s+/);
  const stack = [];

  for (let token of tokens) {
    if (!isNaN(token) || token === "π" || token === "e" || /^-?\d+(\.\d+)?$/.test(token)) {
      stack.push(`<mn>${token}</mn>`);
    } else if (["sqrt", "sin", "cos", "tan", "ln", "log", "abs", "neg", "exp", "floor", "ceil"].includes(token)) {
      const arg = stack.pop();
      if (!arg) {
        stack.push(`<mtext>⚠️ Eroare</mtext>`);
        continue;
      }

      switch (token) {
        case "sqrt": stack.push(`<msqrt>${arg}</msqrt>`); break;
        case "abs": stack.push(`<mrow><mo>|</mo>${arg}<mo>|</mo></mrow>`); break;
        case "neg": stack.push(`<mrow><mo>-</mo>${arg}</mrow>`); break;
        case "floor": stack.push(`<mrow><mo>⌊</mo>${arg}<mo>⌋</mo></mrow>`); break;
        case "ceil": stack.push(`<mrow><mo>⌈</mo>${arg}<mo>⌉</mo></mrow>`); break;
        default: stack.push(`<mrow><mi>${token}</mi><mo>(</mo>${arg}<mo>)</mo></mrow>`); break;
      }
    } else if (["+", "-", "*", "/", "^", "%"].includes(token)) {
      const b = stack.pop();
      const a = stack.pop();
      if (!a || !b) {
        stack.push(`<mtext>⚠️ Eroare</mtext>`);
        continue;
      }

      switch (token) {
        case "^":
          stack.push(`<msup><mrow>${a}</mrow><mrow>${b}</mrow></msup>`);
          break;
        default:
          stack.push(`<mrow><mo>(</mo>${a}<mo> ${token} </mo>${b}<mo>)</mo></mrow>`);
      }
    } else {
      stack.push(`<mtext>❓ ${token}</mtext>`);
    }
  }

  const final = stack.pop() || `<mtext>⚠️ Expresie invalidă</mtext>`;
  const mathML = `<math xmlns="http://www.w3.org/1998/Math/MathML">${final}</math>`;

  const container = document.getElementById(containerId);
  container.innerHTML = mathML;

  if (window.MathJax && window.MathJax.typesetPromise) {
    MathJax.typesetClear();
    MathJax.typesetPromise([container]).then(() => {
      console.log("✅ MathML randat pentru postfix:", expr);
    }).catch(err => console.error("❌ MathJax error:", err));
  }
}


function importHistoryFile(event) {
  const file = event.target.files[0];
  const reader = new FileReader();

  reader.onload = () => {
    const content = reader.result;
    
    const oldLength = HistoryModel.expressions.length;

    const success = file.name.endsWith(".json")
      ? HistoryModel.importJSON(content)
      : HistoryModel.importXML(content);

    if (!success) {
      alert("Fișier invalid.");
      return;
    }

    updateHistoryUI(); 

    const newEntries = HistoryModel.expressions.slice(oldLength);
    importedExprList = newEntries.map(e => e.expr);
    importedExprIndex = 0;

    if (importedExprList.length > 0) {
      showImportedExpr(importedExprList[importedExprIndex]);
    }

    updateNavigationButtons();
  };

  reader.readAsText(file);
}


function showImportedExpr(expr) {
  currentExpr = expr;
  document.getElementById("inputExpr").value = expr;
  const isPrefix = document.title.includes("Prefix");
  if (isPrefix) {
    evaluatePrefixExpr(false);
  } else {
    evaluatePostfixExpr(false);
  }
  updateNavigationButtons();
}

function updateNavigationButtons() {
  const prevBtn = document.getElementById("prevImportedExprBtn");
  const nextBtn = document.getElementById("nextImportedExprBtn");

  prevBtn.style.display = importedExprIndex > 0 ? "inline-block" : "none";
  nextBtn.style.display = importedExprIndex < importedExprList.length - 1 ? "inline-block" : "none";
}

function nextImportedExpr() {
  if (importedExprIndex < importedExprList.length - 1) {
    importedExprIndex++;
    showImportedExpr(importedExprList[importedExprIndex]);
  }
}


function prevImportedExpr() {
  if (importedExprIndex > 0) {
    importedExprIndex--;
    showImportedExpr(importedExprList[importedExprIndex]);
  } 
}


function evaluatePrefixExpr(saveToHistory = true) {
  const inputText = document.getElementById('inputExpr').value.trim();
  const tokens = tokenize(inputText);
  const steps = [];
  let result = null;
  let tree = null;

  try {
    [result, tree] = solvePrefix(tokens, steps);
  } catch (err) {
    console.error("❌ Eroare în solvePrefix:", err);
  }

  if (result === null) {
document.getElementById('output').textContent = result !== null ? result : "Expresie invalidă";
    document.getElementById("steps").innerHTML = "";
    //document.getElementById("tree").innerHTML = "";
    document.getElementById("mathmlView").innerHTML = "";
    document.getElementById("svgTree").innerHTML = "";
    return;
  }

  document.getElementById('output').textContent = result;

  const stepsContainer = document.getElementById('steps');
  stepsContainer.innerHTML = "<h3>Pași de evaluare:</h3>";
  steps.forEach(step => {
    const li = document.createElement('li');
    li.textContent = step;
    stepsContainer.appendChild(li);
  });

  const treeContainer = document.getElementById('tree');
  if (treeContainer) treeContainer.innerHTML = "";

 if (result !== null && tree) {
  renderSVGTree(tree);
  generateMathML(tokens.map(([t]) => t).join(" "), 'mathmlView');
}

  if (saveToHistory) {
    currentExampleIndex = null;
    HistoryModel.add(inputText);
    currentExpr = inputText;
    const username = sessionStorage.getItem("username");
if (username) {
  fetch(`/api/history/${username}`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ expressions: HistoryModel.expressions })
  });
}

    updateHistoryUI();
  }
}

function renderSVGTree(root) {
  const svg = document.getElementById("svgTree");
  svg.innerHTML = "";
  if (!root) return;

  const nodeRadius = 20;
  const verticalSpacing = 60;
  const horizontalSpacing = 40;
  let maxY = 0;
  let maxX = 0;
  let leafCount = 0;

  function assignCoordinates(node, depth = 0) {
    if (!node) return;

    if (!node.left && !node.right) {
      node.x = leafCount * horizontalSpacing * 2 + 50;
      node.y = depth * verticalSpacing + 40;
      leafCount++;
    } else {
      assignCoordinates(node.left, depth + 1);
      assignCoordinates(node.right, depth + 1);
      const children = [node.left, node.right].filter(Boolean);
      node.x = (children.reduce((sum, c) => sum + c.x, 0)) / children.length;
      node.y = depth * verticalSpacing + 40;
    }

    maxX = Math.max(maxX, node.x);
    maxY = Math.max(maxY, node.y);
  }

  function drawNode(node) {
    if (!node) return;

    const circle = document.createElementNS("http://www.w3.org/2000/svg", "circle");
    circle.setAttribute("cx", node.x);
    circle.setAttribute("cy", node.y);
    circle.setAttribute("r", nodeRadius);
    circle.setAttribute("fill", "#4A90E2");
    svg.appendChild(circle);

    const text = document.createElementNS("http://www.w3.org/2000/svg", "text");
    text.setAttribute("x", node.x);
    text.setAttribute("y", node.y + 5);
    text.setAttribute("text-anchor", "middle");
    text.setAttribute("fill", "white");
    text.setAttribute("font-size", "14");

    let displayValue = node.value;

switch (displayValue) {
  case "neg": displayValue = "-"; break;
  case "pi":
  case "3.141592653589793": displayValue = "π"; break;
  case "e":
  case "2.718281828459045": displayValue = "e"; break;
  case "sqrt": displayValue = "√"; break;
  case "ln": displayValue = "ln"; break;
  case "log": displayValue = "log"; break;
  case "abs": displayValue = "|x|"; break;
  case "floor": displayValue = "⌊x⌋"; break;
  case "ceil": displayValue = "⌈x⌉"; break;
  case "sin": displayValue = "sin"; break;
  case "cos": displayValue = "cos"; break;
  case "tan": displayValue = "tan"; break;
  case "exp": displayValue = "exp"; break;
}

    text.textContent = displayValue;
    svg.appendChild(text);

    if (node.left) {
      const line = document.createElementNS("http://www.w3.org/2000/svg", "line");
      line.setAttribute("x1", node.x);
      line.setAttribute("y1", node.y + nodeRadius);
      line.setAttribute("x2", node.left.x);
      line.setAttribute("y2", node.left.y - nodeRadius);
      line.setAttribute("stroke", "black");
      svg.appendChild(line);
      drawNode(node.left);
    }

    if (node.right) {
      const line = document.createElementNS("http://www.w3.org/2000/svg", "line");
      line.setAttribute("x1", node.x);
      line.setAttribute("y1", node.y + nodeRadius);
      line.setAttribute("x2", node.right.x);
      line.setAttribute("y2", node.right.y - nodeRadius);
      line.setAttribute("stroke", "black");
      svg.appendChild(line);
      drawNode(node.right);
    }
  }

  assignCoordinates(root);
  drawNode(root);
  svg.setAttribute("height", maxY + 60);
  svg.setAttribute("viewBox", `0 0 ${maxX + 100} ${maxY + 60}`);
  svg.setAttribute("width", "100%");
}
function hideImportButtons() {
  document.getElementById("nextImportedExprBtn").style.display = "none";
  document.getElementById("prevImportedExprBtn").style.display = "none";
  importedExprList = [];
  importedExprIndex = 0;
}
