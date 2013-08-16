var qt = require('./'),
    app = new qt.QApplication,
    window = new qt.QWidget,
    edit = new qt.QTextEdit(window);

// Prevent objects from being GC'd
global.app = app;
global.window = window;
global.edit = edit;

window.closeEvent(function (e) {
  process.exit(0);
});

window.resizeEvent(function (e) {
  var s = e.size();
  edit.resize(s.width() - 10, s.height() - 10);
});

window.resize(400, 200);
window.move(300, 300);
window.setWindowTitle('Notepad');

edit.move(5, 5);

window.show();

// Join Node's event loop
setInterval(function () {
  app.processEvents();
}, 0);

