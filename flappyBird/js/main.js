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
var constant = tubeDownward.height + gap;
var birdCoordinate = {
  x : 75,
  y : 200
};
var gravity = 1.5;

document.addEventListener("keydown", function (event) {
  event.preventDefault();
  if (event.keyCode == 32){
    goUp();
  }
});
function goUp() {
  var y = birdCoordinate.y;
  $(birdCoordinate).animate({
    y : y-95,
  },200);
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

    tubes[i].x--;
    tubes[i].x--;

    if ( tubes[i].x == 1000){
      tubes.push({
        y : Math.floor(Math.random() * tubeDownward.height) - tubeDownward.height,
        x : cvs.width
      });
    }
    if (birdCoordinate.x + flyingObjectImage.width >= tubes[i].x && birdCoordinate.x <= tubes[i].x + tubeDownward.width
      && (birdCoordinate.y <= tubes[i].y + tubeDownward.height || birdCoordinate.y + flyingObjectImage.height >= tubes[i].y + constant)
      || (birdCoordinate.y + flyingObjectImage.height >= canvas.height) || birdCoordinate.y < -200
    ){
      location.reload(); //reload the page
      scoreCounter = 0;
    }
    if (tubes[i].x + tubeDownward.width == 0){
      scoreCounter += 5;
    }
  }
  ctx.drawImage(flyingObjectImage, birdCoordinate.x, birdCoordinate.y);
  var score = "Score: ";
  ctx.fillText(score, 75, window.innerHeight-5);
  scorePoint = String(scoreCounter);
  ctx.fillText(scorePoint, ctx.measureText(score).width + 65, window.innerHeight-5);
  gravity = gravity * 1.025;
  birdCoordinate.y += gravity;
  requestAnimationFrame(drawTheObjects);
}
drawTheObjects();
