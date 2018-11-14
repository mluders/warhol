const lottie = require('../lib/lottie')

function renderAnimationData(animData) {
  console.log('Starting render');
  const canvas = document.createElement('canvas');
  const ctx = canvas.getContext('2d');  

  const anim = lottie.loadAnimation({
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

  anim.addEventListener('DOMLoaded', function() {
    anim.goToAndStop(0);
    let data = ctx.getImageData(0, 0, canvas.width, canvas.height).data;
    console.log(data);
  });
}

exports.renderAnimationData = renderAnimationData;
