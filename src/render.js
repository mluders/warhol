const lottie = require('../lib/lottie');
const gifster = require('./gifster/build/Release/gifster');

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

function createAnimation(cv_ctx) {
  let anim = lottie.loadAnimation({
    renderer: "canvas",
    loop: false,
    autoplay: false,
    rendererSettings: {
      context: cv_ctx,
      scaleMode: "noScale",
      clearCanvas: true
    },
    path: "../designs/welcome.json"
  });
  return anim;
}

function renderAnimationData(animData) {
  const helloCanvas = createCanvas(300, 150);
  const helloCanvasCtx = helloCanvas.getContext("2d");
  const helloAnim = createAnimation(helloCanvasCtx);

  helloAnim.addEventListener("DOMLoaded", function() {
    gifster.create_gif(helloCanvas.width, helloCanvas.height, 100, true);

    for (let i=0; i<150; i++) {
      helloAnim.goToAndStop(i, true);
      const arr = helloCanvasCtx.getImageData(0, 0, helloCanvas.width, helloCanvas.height).data;
      gifster.add_frame(arr);
    }
    gifster.end_adding_frames(function(message) {
      console.log(message);
    });
  });
}

exports.renderAnimationData = renderAnimationData;
