const lottie = require('../lib/lottie');
const gifster = require('./gifster/build/Release/gifster');
const uuidv4 = require('uuid/v4');
const outDir = '../out';

function generateOutputPath(ext='gif') {
  return outDir + '/' + uuidv4() + '.' + ext;
}

function createCanvas(w, h) {
  let div = document.createElement("div");
  div.setAttribute("class", "anim-div");

  let cv = document.createElement("canvas");
  cv.setAttribute("class", "anim-canvas");
  cv.setAttribute("width", w);
  cv.setAttribute("height", h);
  div.appendChild(cv);

  document.body.appendChild(div);
  return cv;
}

function createAnimation(animData, ctx) {
  let anim = lottie.loadAnimation({
    renderer: 'canvas',
    loop: false,
    autoplay: false,
    rendererSettings: {
      context: ctx,
      scaleMode: 'noScale',
      clearCanvas: true
    },
    animationData: animData
  });
  
  return anim;
}

function renderAnimationData(animData, onComplete) {
  const canvas = createCanvas(300, 150);
  const ctx = canvas.getContext("2d");
  const anim = createAnimation(animData, ctx);
  const outPath = generateOutputPath();

  anim.addEventListener("DOMLoaded", function() {
    gifster.create_gif(canvas.width, canvas.height, 100, true);

    for (let i=0; i<anim.totalFrames; i++) {
      anim.goToAndStop(i, true);
      const data = ctx.getImageData(0, 0, canvas.width, canvas.height).data;
      gifster.add_frame(data);
    }
    gifster.end_adding_frames(function(err) {
      onComplete(outPath);
    });
  });
}

exports.renderAnimationData = renderAnimationData;
