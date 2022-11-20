var questionsF = [
    {
        numb: 1,
        question: "Qual desses dispositivos é analógico?",
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
        numb: 2,
        question: "Qual desses dispositivos é analógico?",
        answer: "Sensor LDR",
        options: [
            "Led",
            "Push button",
            "Sensor LDR",
            "Sensor Ultrassônico"
        ]
    }
]

var pointsFirstPlayer = 0
var pointsSecondPlayer = 0

function checkAnswer(id) {
    let index = 0;
    answerSelected = document.getElementById(id).textContent;
    if (answerSelected == questionsF[index].answer) {
        console.log("Acertou");
        pointsFirstPlayer += 1;
        question2()

    }
    else {
        console.log("Errou");
    }
    questionsF.numb += 2;
    index += 1;
}

function question2() {
    
}