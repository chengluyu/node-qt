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
  for (var x = 5; x <= 305; x += 20)
    p.drawLine(x, 5, x, 145);
  for (var y = 5; y <= 145; y += 20)
    p.drawLine(5, y, 305, y);
  p.end();
});

window.leaveEvent(function (e) {
  console.log(e.constructor);
  console.log('Left.');
});

window.enterEvent(function (e) {
  console.log('Entered.');
});

window.closeEvent(function (e) {
  process.exit(0);
});

window.resizeEvent(function (e) {
  console.log("New size:", e.size().width(), e.size().height());
  console.log("Old size:", e.oldSize().width(), e.oldSize().height());
});

window.resize(310, 150);
window.move(300, 300);
window.show();

// Join Node's event loop
setInterval(function () {
  app.processEvents();
}, 0);

