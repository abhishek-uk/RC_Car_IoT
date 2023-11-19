void handleRoot() {
    String html = "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">";
    html +="<body style=\"margin: 25px; display: flex; align-items: flex-end; justify-content: space-between;\">";
    html +="<div style=\"width: 30%; height: 200px; \">";
    html +="<div style=\"width: 100%; height: 100px; display: flex; align-items: top; justify-content: center;\">";
    html +="<button style=\"width: 40%; height: 80%;\" onclick='sendValue(1)'>S</button>";
    html +="</div>";
    html +="<div style=\"width: 100%; height: 100px; display: flex; justify-content: space-around; align-items: center;\" >";
    html +="<button style=\"height: 80%; width: 40%;\" onclick='sendValue(2)'>L</button>";
    html +="<button style=\"height: 80%; width: 40%;\" onclick='sendValue(3)'>R</button>";
    html +="</div>";
    html +="</div>";
    html +="<div style=\"width: 30%; height: 200px; display: flex; justify-content: space-around; align-items: center;\">";
    html +="<div style=\"width: 30%; height: 90%; display: flex; align-items: flex-end;\">";
    html +="<button style=\"height: 40%; width: 100%;\" onclick='sendValue(4)'>E</button>";
    html +="</div>";
    html +="<div style=\"width: 40%; height: 90%; display: flex; flex-direction: column; justify-content: space-between;\">";
    html +="<button style=\"height: 40%; width: 100%;\" onclick='sendValue(5)'>F</button>";
    html +="<button style=\"height: 40%; width: 100%;\" onclick='sendValue(6)'>B</button>";
    html +="</div>";
    html +="</div>";
    html += "<script>";
    html += "function sendValue(valueToSend) {";
    html += "var xhr = new XMLHttpRequest();";
    html += "xhr.open('POST', '/', true);"; ///
    html += "xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');";   ///
    html += "xhr.send('value=' + valueToSend);";
    html += "}";
    html += "</script>";
    html +="</body>";
    server.send(200, "text/html", html);
}