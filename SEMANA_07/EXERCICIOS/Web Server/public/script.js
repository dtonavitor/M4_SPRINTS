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

    },
    {
        question: "Qual o protocolo do RFID?",
        answer: "SPI",
        options: [
            "SPI",
            "I2C",
            "FTM",
            "RSSI"
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
    },
    {

    },
    {
        question: "Qual a porta do fio terra no Display LCD?",
        answer: "GND",
        options: [
            "SDA",
            "SCL",
            "VCC",
            "GND"
        ] 
    }
]

var pointsFirstPlayer = 0
var pointsSecondPlayer = 0
var questionNumber = 1

var indexF = 0;
var indexS = 1;

// Database path for GPIO states
var dbPathOutput1 = 'board1/outputs/digital/16';
var dbPathOutput2 = 'board1/outputs/digital/17';

var dbRefOutput1 = firebase.database().ref().child(dbPathOutput1);
var dbRefOutput2 = firebase.database().ref().child(dbPathOutput2);

function getFinalScreen() {
    let text = '';
    text += `</div>`
    text += '<div class="menu">'
    text += `<h1 id="result"></h1>`
    text +='<h3 id="winner"></h3>'
    text +='<h3 id="pointsf"></h3>'
    text += `<h3 id="second"></h3>`
    text +='<h3 id="pointss"></h3>'
    text +='</div>'
    text +=`<script src="script.js"></script>`
    text +=`<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-OERcA2EqjJCMA+/3y+gxIOqMEjwtxJY7qPCqsdltbNJuaOe923+mo//f6V8Qbsw3" crossorigin="anonymous"></script>`

    document.getElementById('body').innerHTML = text;

    document.getElementById('style_menu').href = '/final.css';

    if (pointsFirstPlayer > pointsSecondPlayer) {
        document.querySelector("#winner").innerHTML = firstPlayer;
        document.querySelector("#second").innerHTML = secondPlayer;
        document.querySelector("#pointsf").innerHTML = pointsFirstPlayer;
        document.querySelector("#pointss").innerHTML = pointsSecondPlayer;
        document.querySelector("#result").innerHTML = `Vencedor: ${firstPlayer}!`;
    }
    else if (pointsFirstPlayer == pointsSecondPlayer) {
        document.querySelector("#result").innerHTML = "Empate";
        document.querySelector("#winner").innerHTML = firstPlayer;
        document.querySelector("#second").innerHTML = secondPlayer;
        document.querySelector("#pointsf").innerHTML = pointsFirstPlayer;
        document.querySelector("#pointss").innerHTML = pointsSecondPlayer;
    }
    else {
        document.querySelector("#result").innerHTML = `Vencedor ${secondPlayer}!`;
        document.querySelector("#winner").innerHTML = secondPlayer;
        document.querySelector("#second").innerHTML = firstPlayer;
        document.querySelector("#pointsf").innerHTML = pointsSecondPlayer;
        document.querySelector("#pointss").innerHTML = pointsFirstPlayer; 
    }
}

function question(questionNumber) {
    let text = '';
    setTimeout(function(){
        dbRefOutput1.set(0);
        dbRefOutput2.set(0);
    }, 1000)
    if (questionNumber <= 4) {  
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

            document.getElementById('style_menu').href = '/question.css';
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

            document.getElementById('style_menu').href = '/question.css';
        }
    }
    else {
        getFinalScreen() 
    }
}

function checkAnswer(id) {
    if (questionNumber % 2 != 0) {
        answerSelected = document.getElementById(id).textContent;
        if (answerSelected == questionsF[indexF].answer) {
            pointsFirstPlayer += 1;
            dbRefOutput2.set(1);
        }
        else {
            dbRefOutput1.set(1);
        }
        questionNumber += 1;
        indexF += 2;
    }
    else {
        answerSelected = document.getElementById(id).textContent;
        if (answerSelected == questionsS[indexS].answer) {
            pointsSecondPlayer += 1;
            dbRefOutput2.set(1);
        }
        else {
            dbRefOutput1.set(1);
        }
        questionNumber += 1;
        indexS += 2;
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