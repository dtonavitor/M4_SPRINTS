var firstPlayer;
var secondPlayer;

var questionsF = [
    {
        question: "Qual desses dispositivos é analógico?",
        answer: "Sensor LDR",
        options: [
            "Led",
            "Push button",
            "Sensor LDR",
            "Sensor Ultrassônico"
        ]
    },
    {
        question: "Qual desses dispositivos é digital?",
        answer: "Sensor LDR",
        options: [
            "Led",
            "Push button",
            "Sensor LDR",
            "Sensor Ultrassônico"
        ] 
    }
]

var questionsS = [
    {

    },
    {
        question: "Qual a utilidade do sensor LDR?",
        answer: "Medir luminosidade",
        options: [
            "Medir umidade",
            "Identificar movimentos",
            "Medir temperatura",
            "Medir luminosidade"
        ]
    }
]

var pointsFirstPlayer = 0
var pointsSecondPlayer = 0
var questionNumber = 1


function question(questionNumber) {
    let text = '';
    if (questionNumber % 2 != 0) {
        text += `<div id="player_question">Pergunta para ${firstPlayer}</div>`
        text += '<div class="question">'
        text += `<h1 id="title">${questionsF[questionNumber - 1].question}</h1>`
        text +='</div>'
        text +='<div class="menu">'
        text +=`<button id="alt1b" value="${questionsF[questionNumber - 1].options[0]}"><p id="alt1" onclick="checkAnswer(this.id)">${questionsF[questionNumber - 1].options[0]}</p></button>`
        text +=`<button id="alt2b" value="${questionsF[questionNumber - 1].options[1]}"><p id="alt2" onclick="checkAnswer(this.id)">${questionsF[questionNumber - 1].options[1]}</p></button>`
        text +=`<button id="alt3b" value="${questionsF[questionNumber - 1].options[2]}"><p id="alt3" onclick="checkAnswer(this.id)">${questionsF[questionNumber - 1].options[2]}</p></button>`
        text += `<button id="alt4b" value="${questionsF[questionNumber - 1].options[3]}"><p id="alt4" onclick="checkAnswer(this.id)">${questionsF[questionNumber - 1].options[3]}</p></button>`
        text +='</div>'
        document.getElementById('body').innerHTML = text;

        document.getElementById('style_menu').href = 'question.css';
    }
    else {
        text += `<div id="player_question">Pergunta para ${secondPlayer}</div>`
        text += '<div class="question">'
        text += `<h1 id="title">${questionsS[questionNumber - 1].question}</h1>`
        text +='</div>'
        text +='<div class="menu">'
        text +=`<button id="alt1b" value="${questionsS[questionNumber - 1].options[0]}"><p id="alt1" onclick="checkAnswer(this.id)">${questionsS[questionNumber - 1].options[0]}</p></button>`
        text +=`<button id="alt2b" value="${questionsS[questionNumber - 1].options[1]}"><p id="alt2" onclick="checkAnswer(this.id)">${questionsS[questionNumber - 1].options[1]}</p></button>`
        text +=`<button id="alt3b" value="${questionsS[questionNumber - 1].options[2]}"><p id="alt3" onclick="checkAnswer(this.id)">${questionsS[questionNumber - 1].options[2]}</p></button>`
        text += `<button id="alt4b" value="${questionsS[questionNumber - 1].options[3]}"><p id="alt4" onclick="checkAnswer(this.id)">${questionsS[questionNumber - 1].options[3]}</p></button>`
        text +='</div>'
        document.getElementById('body').innerHTML = text;

        document.getElementById('style_menu').href = 'question.css';
    }
}

function checkAnswer(id) {
    let indexF = 0;
    let indexS = 0;
    if (questionNumber % 2 != 0) {
        answerSelected = document.getElementById(id).textContent;
        if (answerSelected == questionsF[indexF].answer) {
            console.log("Acertou");
            pointsFirstPlayer += 1;
        }
        else {
            console.log("Errou");
        }
        questionNumber += 1;
        indexF += 1;
    }
    else {
        answerSelected = document.getElementById(id).textContent;
        if (answerSelected == questionsS[indexS].answer) {
            console.log("Acertou");
            pointsSecondPlayer += 1;
        }
        else {
            console.log("Errou");
        }
        questionNumber += 1;
        indexS += 1;
    }
    question(questionNumber);
}

function getNames() {
    firstPlayer = document.getElementById('fplayer').value;
    secondPlayer = document.getElementById('splayer').value;
    if (firstPlayer == "" || secondPlayer == "") {
        document.getElementById("error").innerHTML = "*Insira ambos os nomes!"
    }
    else {
        question(questionNumber);
    }
}