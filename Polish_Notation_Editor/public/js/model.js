function tokenize(str) {
  return str.trim().split(/\s+/).map(tok => {
    if (tok.toLowerCase() === "pi") return ["π", "operand"];
    if (tok.toLowerCase() === "e") return ["e", "operand"];
    if (!isNaN(tok)) return [parseFloat(tok), "operand"];
    if (tok === "(" || tok === ")") return null;
    return [tok, "operator"];
  }).filter(Boolean);
}


function solvePrefix(tokens, steps) {
  const reversed = [...tokens].reverse();

  function helper() {
    if (reversed.length === 0) return [null, null];
    const [val, type] = reversed.pop();

    if (type === "operand") {
      if (val === "π") return [Math.PI, { value: "π" }];
      if (val === "e") return [Math.E, { value: "e" }];
      return [val, { value: val }];
    }

    if (["sqrt", "sin", "cos", "tan", "ln", "log", "abs", "neg", "!", "exp", "floor", "ceil"].includes(val)) {
      const [operand, subTree] = helper();
      if (operand === null) return [null, null];
      let res;
      switch (val) {
        case "sqrt": res = Math.sqrt(operand); break;
        case "sin": res = Math.sin(operand); break;
        case "cos": res = Math.cos(operand); break;
        case "tan": res = Math.tan(operand); break;
        case "ln": res = Math.log(operand); break;
        case "log": res = Math.log10(operand); break;
        case "abs": res = Math.abs(operand); break;
        case "neg": res = -operand; break;
        case "!": res = [...Array(operand | 0).keys()].reduce((acc, x) => acc * (x + 1), 1); break;
        case "exp": res = Math.exp(operand); break;
        case "floor": res = Math.floor(operand); break;
        case "ceil": res = Math.ceil(operand); break;
        default: return [null, null];
      }
      steps.push(`${val} ${operand} = ${res}`);
      return [res, { value: val, left: subTree }];
    }

    const [leftVal, leftTree] = helper();
    const [rightVal, rightTree] = helper();
    if (leftVal === null || rightVal === null) return [null, null];

    let res;
    switch (val) {
      case "+": res = leftVal + rightVal; break;
      case "-": res = leftVal - rightVal; break;
      case "*": res = leftVal * rightVal; break;
      case "/": res = leftVal / rightVal; break;
      case "^": res = Math.pow(leftVal, rightVal); break;
      case "%": res = leftVal % rightVal; break;
      default: return [null, null];
    }
    steps.push(`${leftVal} ${val} ${rightVal} = ${res}`);
    return [res, { value: val, left: leftTree, right: rightTree }];
  }

  const [result, tree] = helper();

  // ✅ dacă au mai rămas tokeni, e invalid
  if (reversed.length !== 0) return [null, null];

  return [result, tree];
}


function renderTree(node, prefix = "", isLeft = true) {
  if (!node) return "";
  let result = prefix;
  result += isLeft ? "└── " : "├── ";
  result += node.value + "\n";

  const hasLeft = node.left !== undefined;
  const hasRight = node.right !== undefined;

  if (hasLeft || hasRight) {
    const newPrefix = prefix + (isLeft ? "    " : "│   ");
    if (hasRight) {
      result += renderTree(node.right, newPrefix, false);
    }
    if (hasLeft) {
      result += renderTree(node.left, newPrefix, true);
    }
  }

  return result;
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


const HistoryModel = {
  expressions: [], 

  add(expr, comment = "") {
  this.expressions.push({ expr, comment });
}
,

  load() {
    const data = localStorage.getItem("exprHistory");
    if (data) {
      const parsed = JSON.parse(data);
      this.expressions = parsed.map(e =>
        typeof e === "string" ? { expr: e, comment: "" } : e
      );
    }
  },

  exportJSON() {
    return JSON.stringify(this.expressions, null, 2);
  },

  exportXML() {
    const xml = this.expressions
      .map((e, i) => `<expr id="${i + 1}"><text>${e.expr}</text><comment>${e.comment}</comment></expr>`)
      .join("");
    return `<history>${xml}</history>`;
  },
importJSON(jsonText) {
  try {
    const parsed = JSON.parse(jsonText);
    if (Array.isArray(parsed)) {
      const newItems = parsed.map(e =>
        typeof e === "string" ? { expr: e, comment: "" } : e
      );
      this.expressions = [...this.expressions, ...newItems]; // ✅ concatenează
      return true;
    }
  } catch {}
  return false;
},

importXML(xmlText) {
  try {
    const parser = new DOMParser();
    const xml = parser.parseFromString(xmlText, "text/xml");
    const nodes = xml.getElementsByTagName("expr");
    const newItems = [];

    for (let node of nodes) {
      const text = node.getElementsByTagName("text")[0]?.textContent || "";
      const comment = node.getElementsByTagName("comment")[0]?.textContent || "";
      newItems.push({ expr: text, comment });
    }

    this.expressions = [...this.expressions, ...newItems]; 
    return true;
  } catch {
    return false;
  }
}
};

function evaluatePostfixExpr(saveToHistory = true) {
  const inputText = document.getElementById('inputExpr').value.trim();
  const tokens = tokenize(inputText);
  const steps = [];
  const [result, tree] = solvePostfix(tokens, steps);

  document.getElementById('output').textContent = result !== null ? result : "Expresie invalidă";

  if (result === null) {
    document.getElementById("steps").innerHTML = "";
    //document.getElementById("tree").innerHTML = "";
    document.getElementById("mathmlView").innerHTML = "";
    document.getElementById("svgTree").innerHTML = "";
    return;
  }

  const stepsContainer = document.getElementById('steps');
  stepsContainer.innerHTML = "<h3>Pași de evaluare:</h3>";
  steps.forEach(step => {
    const li = document.createElement('li');
    li.textContent = step;
    stepsContainer.appendChild(li);
  });

  renderSVGTree(tree);
const rawExpr = tokens.map(([t]) => t).join(" ");
generateMathMLPostfix(rawExpr, 'mathmlView');

  if (result !== null && saveToHistory) {
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


function solvePostfix(tokens, steps) {
  const stack = [];
  const treeStack = [];

  for (let [originalVal, type] of tokens) {
  let val = originalVal;
  let displayVal = originalVal;

  if (val === "π") val = Math.PI;
  if (val === "e") val = Math.E;

    if (type === "operand") {
      stack.push(val);
      treeStack.push({ value: displayVal });
    } else if (["sqrt", "sin", "cos", "tan", "ln", "log", "abs", "neg", "!", "exp", "floor", "ceil"].includes(val)) {
      const a = stack.pop();
      const t = treeStack.pop();
      if (a == null) return [null, null];

      let res;
      switch (val) {
        case "sqrt": res = Math.sqrt(a); break;
        case "sin": res = Math.sin(a); break;
        case "cos": res = Math.cos(a); break;
        case "tan": res = Math.tan(a); break;
        case "ln": res = Math.log(a); break;
        case "log": res = Math.log10(a); break;
        case "abs": res = Math.abs(a); break;
        case "neg": res = -a; break;
        case "!": res = [...Array(a | 0).keys()].reduce((acc, x) => acc * (x + 1), 1); break;
        case "exp": res = Math.exp(a); break;
        case "floor": res = Math.floor(a); break;
        case "ceil": res = Math.ceil(a); break;
        default: return [null, null];
      }

      steps.push(`${val} ${a} = ${res}`);
      stack.push(res);
      treeStack.push({ value: displayVal, left: t });
    } else {
      const b = stack.pop();
      const a = stack.pop();
      const tb = treeStack.pop();
      const ta = treeStack.pop();
      if (a == null || b == null) return [null, null];

      let res;
      switch (val) {
        case "+": res = a + b; break;
        case "-": res = a - b; break;
        case "*": res = a * b; break;
        case "/": res = a / b; break;
        case "^": res = Math.pow(a, b); break;
        case "%": res = a % b; break;
        default: return [null, null];
      }

      steps.push(`${a} ${val} ${b} = ${res}`);
      stack.push(res);
      treeStack.push({ value: displayVal, left: ta, right: tb });
    }
  }

  return stack.length === 1 ? [stack[0], treeStack[0]] : [null, null];
}

