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
  p.drawText(20, 30, 'hello node, hello qt');
  p.end();
});

window.closeEvent(function (args) {
  console.log(args.constructor);
  process.exit(0);
});

window.resize(300, 150);
window.move(300, 300);
window.show();

var rect = new qt.QRect(1, 2, 3, 4);
console.log(rect.x(), rect.y(), rect.width(), rect.height());

// Join Node's event loop
setInterval(function () {
  app.processEvents();
}, 0);

