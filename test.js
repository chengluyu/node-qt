var qt = require('./'),
    app = new qt.QApplication,
    window = new qt.QWidget;

// Prevent objects from being GC'd
global.app = app;
global.window = window;

// Quirk: the virtual method paintEvent() is mapped into a callback setter
window.paintEvent(function () {
  var p = new qt.QPainter();
  p.begin(window);
  p.setRenderHint(qt.RenderHint.Antialiasing);
  p.drawText(20, 30, 'hello node, hello qt');
  p.drawArc(new qt.QRect(10,10, 70,100), 100*16, 160*16);
  p.end();
});

window.closeEvent(function (args) {
  console.log(args.constructor);
  process.exit(0);
});

window.resize(300, 150);
window.move(300, 300);
window.show();

// Join Node's event loop
setInterval(function () {
  app.processEvents();
}, 0);

