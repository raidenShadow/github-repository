var cvs = document.getElementById('canvas');
cvs.width  = document.body.clientWidth;
cvs.height = document.documentElement.clientHeight;
var ctx = cvs.getContext("2d");
ctx.font = "60px Comic Sans MS";
var flyingObjectImage = new Image();
var tubeUpward = new Image();
var tubeDownward = new Image();
var background = new Image();
var scoreCounter = 0;
var scorePoint = String(scoreCounter);
background.src = "img/background.png";
flyingObjectImage.src = "img/myFlyingObject.png";
tubeUpward.src = "img/tube-pulled.png";
tubeDownward.src = "img/tube-pulled-reversed.png";
var gap = 200;
const constant = tubeDownward.height + gap;
var birdXCoordinate = 25;
var birdYCoordinate = 200;
var gravity = 1.25;
document.addEventListener("keydown", function (event) {
  event.preventDefault();
  if (event.keyCode == 32){
    goUp();
  }
});
function goUp() {
  birdYCoordinate += -75;
  gravity = 1;
}
var tubes = [];
tubes[0] = {
  x : cvs.width,
  y : 0
}
function drawTheObjects() {
  ctx.drawImage(background, 0 ,0);
  for (var i = 0; i < tubes.length; i++){
    ctx.drawImage(tubeDownward, tubes[i].x, tubes[i].y);
    ctx.drawImage(tubeUpward, tubes[i].x, tubes[i].y+constant);

    if (i >= 4){
      gap -= 50;
    }
    if (i >= 10){
      gap -= 50;
    }
    tubes[i].x -= 4;
    if ( tubes[i].x == 1000){
      tubes.push({
        y : Math.floor(Math.random() * tubeDownward.height) - tubeDownward.height,
        x : cvs.width
      });
    }
    if (birdXCoordinate + flyingObjectImage.width >= tubes[i].x && birdXCoordinate <= tubes[i].x + tubeDownward.width
      && (birdYCoordinate <= tubes[i].y + tubeDownward.height || birdYCoordinate + flyingObjectImage.height >= tubes[i].y + constant)
      || (birdYCoordinate + flyingObjectImage.height >= canvas.height) || (birdYCoordinate <= 0)
    ){
      scoreCounter = 0;
      location.reload(); //reload the page
    }
    if (tubes[i].x + tubeDownward.width == 0){
      scoreCounter += 5;
    }
  }
  ctx.drawImage(flyingObjectImage, birdXCoordinate, birdYCoordinate);
  var score = "Score: ";
  ctx.fillText(score, 5, window.innerHeight-5);
  scorePoint = String(scoreCounter);
  ctx.fillText(scorePoint, ctx.measureText(score).width, window.innerHeight-5);
  gravity = gravity * 1.04;
  birdYCoordinate += gravity;
  requestAnimationFrame(drawTheObjects);
}
drawTheObjects();
