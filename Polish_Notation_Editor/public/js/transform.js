let importedExprList = [];
let importedExprIndex = 0;
let lastImportedOnly = [];


function isOperator(c) {
  return ['+', '-', '*', '/', '^'].includes(c);
}

function isUnaryFunction(token) {
  return ['sqrt', 'sin', 'cos', 'tan', 'ln', 'log', 'abs', 'neg', 'exp', 'floor', 'ceil'].includes(token);
}

function precedence(op) {
  switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    case '^': return 3;
    case 'sqrt': case 'log': case 'abs': case 'exp':
    case 'ln': case 'sin': case 'cos': case 'tan':
    case 'neg': case 'floor': case 'ceil': return 4;
    default: return 0;
  }
}
function isRightAssociative(op) {
  return op === '^';
}
function preprocessUnaryMinus(expr) {
expr = expr.replace(/\bpi\b/g, '3.141592653589793');
  return expr.replace(/(^|[\(\+\-\*\/\^])\s*-\s*(π|e|\d+(\.\d+)?)/g, (_, before, number) => {
    return `${before} neg(${number})`;
  });
}


function tokenizeInfix(expr) {
  const result = [];
  const cleaned = expr.replace(/\s+/g, '');
  const regex = /(sqrt|sin|cos|tan|ln|log|abs|neg|exp|floor|ceil|\^|\+|\-|\*|\/|\(|\)|π|e|\d+(\.\d+)?)/g;
  const tokens = cleaned.match(regex);

  if (!tokens) throw new Error("Expresie invalidă.");

  for (let i = 0; i < tokens.length; i++) {
    const token = tokens[i];

        if (token === '-' &&
    (i === 0 || ['+', '-', '*', '/', '^', '(', ','].includes(tokens[i - 1])) &&
    i + 1 < tokens.length && !isNaN(tokens[i + 1])) {
  // minus unar valid
  result.push('-' + tokens[i + 1]);
  i++;
} else {
  result.push(token); // este minus binar normal
}
  }
  return result;
}

function isValidInfixExpression(expr) {
  const cleaned = expr.replace(/\s+/g, '');

  // 1. Caractere invalide
  const allowedFunctions = ['sqrt', 'sin', 'cos', 'tan', 'ln', 'log', 'abs', 'neg', 'exp', 'floor', 'ceil'];
const cleanedExpr = expr.replace(/\s+/g, '').toLowerCase();
const tempExpr = cleanedExpr.replace(/\b(?:sqrt|sin|cos|tan|ln|log|abs|neg|exp|floor|ceil)\b/g, ''); // elimină funcțiile
const withPi = tempExpr.replace(/\bpi\b/g, '');

// Verifică dacă rămân caractere interzise
if (/[^0-9\+\-\*\/\^\(\)\.\seπ,]/.test(withPi)) {
  return false;
}



  // 2. Paranteze dezechilibrate
  let balance = 0;
  for (const char of cleaned) {
    if (char === '(') balance++;
    else if (char === ')') balance--;
    if (balance < 0) return false;
  }
  if (balance !== 0) return false;

  // 3. Paranteze goale
  if (/\(\)/.test(cleaned)) return false;

  // 4. Doi operatori consecutivi
  if (/[\+\-\*\/\^]{2,}/.test(cleaned)) return false;

  // 5. Lipsă operator între doi operanzi
  if (/\d+\s+\d+/.test(expr)) return false;

  // 6. Operator la final
  if (/[\+\-\*\/\^]\s*$/.test(expr)) return false;

  // 7. Operator la început (fără minus unar sau paranteză)
  if (/^\s*[\+\*\/\^]/.test(expr)) return false;

  // 8. Funcție fără argument: ex: sqrt()
  if (/\b(sqrt|log|ln|abs|neg|exp|floor|ceil|sin|cos|tan)\s*\(\s*\)/.test(expr)) return false;

  return true;
}



function infixToPostfix(infix) {
  const stack = [];
  const output = [];
  const tokens = tokenizeInfix(infix);

    for (let token of tokens) {
if (!isNaN(token) || ['π', 'e', '-π', '-e'].includes(token) || /^-?\\d+(\\.\\d+)?$/.test(token)) {
    output.push(token);

    } else if (isUnaryFunction(token)) {
      stack.push(token);
    } else if (token === '(') {
      stack.push(token);
    } else if (token === ')') {
      while (stack.length && stack[stack.length - 1] !== '(') {
        output.push(stack.pop());
      }
      if (!stack.length) throw new Error("Paranteză închisă fără deschidere.");
      stack.pop();
      if (stack.length && isUnaryFunction(stack[stack.length - 1])) {
        output.push(stack.pop());
      }
    } else if (isOperator(token)) {
      while (
        stack.length &&
        isOperator(stack[stack.length - 1]) &&
        precedence(token) < precedence(stack[stack.length - 1]) ||
(precedence(token) === precedence(stack[stack.length - 1]) && !isRightAssociative(token))

      ) {
        output.push(stack.pop());
      }
      stack.push(token);
    } else {
      throw new Error("Token invalid: " + token);
    }
  }

  while (stack.length) {
    const top = stack.pop();
    if (top === '(') throw new Error("Paranteză deschisă fără închidere.");
    output.push(top);
  }

  return output.join(' ');
}
function infixToPrefix(infix) {
  const preprocessed = preprocessUnaryMinus(infix);
  const tokens = tokenizeInfix(preprocessed);
  const operators = [];
  const operands = [];

  for (const token of tokens) {
if (!isNaN(token) || ['π', 'e', '-π', '-e'].includes(token) || /^-?\\d+(\\.\\d+)?$/.test(token)) {
      operands.push(token);

    } else if (token === '(') {
      operators.push(token);

    } else if (token === ')') {
      while (operators.length && operators[operators.length - 1] !== '(') {
        const op = operators.pop();
        const a = operands.pop();
        const b = isUnaryFunction(op) ? null : operands.pop();
        operands.push(op + " " + (b ? b + " " : "") + a);
      }
      operators.pop(); // scoate '('
      if (operators.length && isUnaryFunction(operators[operators.length - 1])) {
        const func = operators.pop();
        const a = operands.pop();
        operands.push(func + " " + a);
      }

    } else if (isUnaryFunction(token)) {
      operators.push(token);

    } else if (isOperator(token)) {
      while (
        operators.length &&
        operators[operators.length - 1] !== '(' &&
        (
          precedence(token) < precedence(operators[operators.length - 1]) ||
          (precedence(token) === precedence(operators[operators.length - 1]) && !isRightAssociative(token))
        )
      ) {
        const op = operators.pop();
        const a = operands.pop();
        const b = isUnaryFunction(op) ? null : operands.pop();
        operands.push(op + " " + (b ? b + " " : "") + a);
      }
      operators.push(token);
    }
  }

  while (operators.length) {
    const op = operators.pop();
    const a = operands.pop();
    const b = isUnaryFunction(op) ? null : operands.pop();
    operands.push(op + " " + (b ? b + " " : "") + a);
  }

  return operands.pop();
}

function evaluatePrefix(expr) {
  const tokens = expr.trim().split(/\s+/).reverse();

  function helper() {
    if (tokens.length === 0) return null;
    const token = tokens.pop();

    if (!isNaN(token)) return parseFloat(token);
    if (token === "π") return Math.PI;
    if (token === "e") return Math.E;

    if (isUnaryFunction(token)) {
      const val = helper();
      switch (token) {
        case "sqrt": return Math.sqrt(val);
        case "log": return Math.log10(val);
        case "ln": return Math.log(val);
        case "abs": return Math.abs(val);
        case "neg": return -val;
        case "exp": return Math.exp(val);
        case "floor": return Math.floor(val);
        case "ceil": return Math.ceil(val);
        case "sin": return Math.sin(val);
        case "cos": return Math.cos(val);
        case "tan": return Math.tan(val);
      }
    }

    const left = helper();
    const right = helper();

    switch (token) {
      case '+': return left + right;
      case '-': return left - right;
      case '*': return left * right;
      case '/': return left / right;
      case '^': return Math.pow(left, right);
      default: throw new Error("Operator necunoscut: " + token);
    }
  }

  return helper();
}

function buildTreeFromPrefix(expr) {
  const tokens = expr.trim().split(/\s+/).reverse();

  function build() {
    const val = tokens.pop();
    const node = { value: val };

    if (isUnaryFunction(val)) {
      node.left = build();
    } else if (isOperator(val)) {
      node.left = build();
      node.right = build();
    }

    return node;
  }

  return build();
}

function renderTree(node, prefix = '', isLeft = true) {
  if (!node) return '';
  let result = prefix;
  result += isLeft ? '└── ' : '├── ';
let displayValue = node.value;
if (displayValue === 'neg') displayValue = '-';
if (displayValue === 'pi' || displayValue === '3.141592653589793') displayValue = 'π';
result += displayValue + '\n';

  const hasLeft = node.left !== undefined;
  const hasRight = node.right !== undefined;

  if (hasLeft || hasRight) {
    const newPrefix = prefix + (isLeft ? '    ' : '│   ');
    if (hasLeft) result += renderTree(node.left, newPrefix, true);
    if (hasRight) result += renderTree(node.right, newPrefix, false);
  }

  return result;
}

function generateMathML(expr, containerId) {
  const tokens = expr.trim().split(/\s+/);

  function build(tokens) {
    if (tokens.length === 0) return "";

    const token = tokens.shift();

    if (!isNaN(token) || token === "π" || token === "e" || /^-?\d+(\.\d+)?$/.test(token)) {
      return `<mn>${token}</mn>`;
    }

    if (isUnaryFunction(token)) {
      const arg = build(tokens);
      switch (token) {
        case "sqrt":
          return `<msqrt>${arg}</msqrt>`;
        case "abs":
          return `<mrow><mo>|</mo>${arg}<mo>|</mo></mrow>`;
        case "neg":
          return `<mrow><mo>-</mo>${arg}</mrow>`;
        default:
          return `<mrow><mi>${token}</mi><mo>(</mo>${arg}<mo>)</mo></mrow>`;
      }
    }

    // operator binar
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
    MathJax.typesetClear(); // 🧼 curăță eventualele erori
    MathJax.typesetPromise([container]);
  }
}


function generateMathMLPostfix(expr, containerId) {
  const tokens = expr.trim().split(/\s+/);

  function build() {
    const stack = [];

    for (let token of tokens) {
      if (!isNaN(token) || token === "π" || token === "e" || /^-?\d+(\.\d+)?$/.test(token)) {
        stack.push(`<mn>${token}</mn>`);
      } else if (isUnaryFunction(token)) {
        const arg = stack.pop();
        stack.push(`<mrow><mo>${token}</mo><mo>(</mo>${arg}<mo>)</mo></mrow>`);
      } else {
        const b = stack.pop();
        const a = stack.pop();
        stack.push(`<mrow><mo>(</mo>${a}<mo> ${token} </mo>${b}<mo>)</mo></mrow>`);
      }
    }

    return stack.pop();
  }

  const mathML = `<math xmlns="http://www.w3.org/1998/Math/MathML">${build()}</math>`;
  const container = document.getElementById(containerId);
  container.innerHTML = mathML;
  MathJax.typesetPromise([container]);
}

function renderSVGTree(root) {
    let maxY = 0;
  const svg = document.getElementById("svgTree");
  svg.innerHTML = "";
  if (!root) return;

  const nodeRadius = 20;
  const verticalSpacing = 60;
  const horizontalSpacing = 40;
  let maxX = 0;

  function countLeaves(node) {
    if (!node.left && !node.right) return 1;
    return (node.left ? countLeaves(node.left) : 0) + (node.right ? countLeaves(node.right) : 0);
  }

  function layout(node, x, y) {
    if (!node) return null;
    maxY = Math.max(maxY, y);

    const group = document.createElementNS("http://www.w3.org/2000/svg", "g");

    const circle = document.createElementNS("http://www.w3.org/2000/svg", "circle");
    circle.setAttribute("cx", x);
    circle.setAttribute("cy", y);
    circle.setAttribute("r", nodeRadius);
    circle.setAttribute("fill", "#4A90E2");
    group.appendChild(circle);

    const text = document.createElementNS("http://www.w3.org/2000/svg", "text");
    text.setAttribute("x", x);
    text.setAttribute("y", y + 5);
    text.setAttribute("text-anchor", "middle");
    text.setAttribute("fill", "white");
    text.setAttribute("font-size", "14");
let displayValue = node.value;
if (displayValue === "neg") displayValue = "-";
else if (displayValue === "pi" || displayValue === "3.141592653589793") displayValue = "π";
else if (displayValue === "e" || displayValue === "2.718281828459045") displayValue = "e";
else if (displayValue === "sqrt") displayValue = "√";
else if (displayValue === "ln") displayValue = "ln";
else if (displayValue === "log") displayValue = "log";
else if (displayValue === "abs") displayValue = "|x|";
else if (displayValue === "floor") displayValue = "⌊x⌋";
else if (displayValue === "ceil") displayValue = "⌈x⌉";
else if (displayValue === "sin") displayValue = "sin";
else if (displayValue === "cos") displayValue = "cos";
else if (displayValue === "tan") displayValue = "tan";
else if (displayValue === "exp") displayValue = "exp";

text.textContent = displayValue;
    group.appendChild(text);

    svg.appendChild(group);

    const childCount = countLeaves(node);
    const spacing = horizontalSpacing * childCount;

    if (node.left) {
      const childX = x - spacing;
      const childY = y + verticalSpacing;

      const line = document.createElementNS("http://www.w3.org/2000/svg", "line");
      line.setAttribute("x1", x);
      line.setAttribute("y1", y + nodeRadius);
      line.setAttribute("x2", childX);
      line.setAttribute("y2", childY - nodeRadius);
      line.setAttribute("stroke", "black");
      svg.appendChild(line);

      layout(node.left, childX, childY);
    }

    if (node.right) {
      const childX = x + spacing;
      const childY = y + verticalSpacing;

      const line = document.createElementNS("http://www.w3.org/2000/svg", "line");
      line.setAttribute("x1", x);
      line.setAttribute("y1", y + nodeRadius);
      line.setAttribute("x2", childX);
      line.setAttribute("y2", childY - nodeRadius);
      line.setAttribute("stroke", "black");
      svg.appendChild(line);

      layout(node.right, childX, childY);
    }

    maxX = Math.max(maxX, x);
  }

  layout(root, 400, 40);
  svg.setAttribute("height", maxY + 60); // auto-ajustare înălțime
  svg.setAttribute("viewBox", `0 0 ${maxX + 100} ${maxY + 60}`);
svg.setAttribute("width", "100%");

}
function showImportedExpr(expr) {
    currentExpr = expr;
  document.getElementById("inputExpr").value = expr;
  evaluateTransformExpr(false);
  updateNavigationButtons(); // ✅ adaugă aici
}


function nextImportedExpr() {
  importedExprIndex++;
  if (importedExprIndex >= importedExprList.length) {
    alert("Ai ajuns la ultima expresie importata.");
    return;
  }

  showImportedExpr(importedExprList[importedExprIndex]);
}
function prevImportedExpr() {
  if (importedExprIndex <= 0) {
    alert("Aceasta este prima expresie importată.");
    return;
  }

  importedExprIndex--;
  showImportedExpr(importedExprList[importedExprIndex]);
}
function updateNavigationButtons() {
  const prevBtn = document.getElementById("prevImportedExprBtn");
  const nextBtn = document.getElementById("nextImportedExprBtn");

  prevBtn.style.display = importedExprIndex > 0 ? "inline-block" : "none";
  nextBtn.style.display = importedExprIndex < importedExprList.length - 1 ? "inline-block" : "none";
}
function hideImportButtons() {
  document.getElementById("nextImportedExprBtn").style.display = "none";
  document.getElementById("prevImportedExprBtn").style.display = "none";
  importedExprList = [];
  importedExprIndex = 0;
}
