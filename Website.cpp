#include "Website.h"

const char MAIN_PAGE[] = R"rawliteral(






<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">

<title>Skibidibidee Robot</title>

<style>
body{
    font-family:Arial;
    text-align:center;
    margin:20px;
}

button{
    font-size:18px;
    padding:12px;
    margin:4px;
    min-width:110px;
}

.active{
    background-color:green;
    color:white;
}
</style>

<script>
function setMode(mode)
{
    fetch('/' + mode);

   if(mode === 'gesture')
{
    document.getElementById(
        "cameraSection"
    ).style.display = "none";

    document.getElementById(
        "cameraFeed"
    ).src = "";

    cameraOpen = false;
}
else
{
    document.getElementById(
        "cameraSection"
    ).style.display = "block";
}

    if(mode === 'manual')
    {
        document.getElementById('manualBtn').classList.add('active');
        document.getElementById('gestureBtn').classList.remove('active');
    }
    else
    {
        document.getElementById('gestureBtn').classList.add('active');
        document.getElementById('manualBtn').classList.remove('active');
    }
}

window.onload = function()
{
    document.getElementById('manualBtn').classList.add('active');
};

function connectWifi()
{
    let ssid =
        document.getElementById('ssid').value;

    let password =
        document.getElementById('password').value;

    fetch(
        '/connectwifi?ssid=' +
        encodeURIComponent(ssid) +
        '&password=' +
        encodeURIComponent(password)
    )
    .then(r => r.text())
    .then(t =>
    {
        document.getElementById(
            'wifiStatus'
        ).innerHTML = t;
    });
}

let cameraOpen = false;

function toggleCamera()
{
    let img =
        document.getElementById(
            "cameraFeed"
        );

    let btn =
        document.getElementById(
            "cameraBtn"
        );

    if(cameraOpen)
    {
        img.src = "";
        img.style.display = "none";

        btn.innerHTML =
            "📷 Open Camera";

        cameraOpen = false;
    }
    else
    {
        img.src = "/stream";
        img.style.display = "block";

        btn.innerHTML =
            "📷 Close Camera";

        cameraOpen = true;
    }
}

</script>

<!------------------------- webpage ------------------------------->

</head>

<body>

<h1>Skibidibidee Robot</h1>

<hr>

<div id="cameraSection">

<h2>Camera</h2>

<button id="cameraBtn"
        onclick="toggleCamera()">
📷 Open Camera
</button>

<br><br>

<img
    id="cameraFeed"
    src=""
    width="320"
    style="
        display:none;
        border:1px solid #444;
        border-radius:10px;
    ">
<hr>

    </div>

<h2>Internet Connection</h2>

SSID:<br>
<input id="ssid"><br><br>

Password:<br>
<input id="password" type="password"><br><br>

<button onclick="connectWifi()">
Connect WiFi
</button>

<p id="wifiStatus"></p>

<hr>

<h2>Mode</h2>

<button id="manualBtn" onclick="setMode('manual')">
Manual
</button>

<button id="gestureBtn" onclick="setMode('gesture')">
Gesture
</button>

<hr>

<h2>Drive</h2>

<button onclick="fetch('/forward')">Forward</button>

<br><br>

<button onclick="fetch('/left')">Left</button>
<button onclick="fetch('/stop')">Stop</button>
<button onclick="fetch('/right')">Right</button>

<br><br>

<button onclick="fetch('/backward')">Backward</button>

<hr>

<h2>Expressions</h2>

<button onclick="fetch('/normal')">Normal</button>
<button onclick="fetch('/happy')">Happy</button>
<button onclick="fetch('/sad')">Sad</button>

<br>

<button onclick="fetch('/angry')">Angry</button>
<button onclick="fetch('/tired')">Tired</button>

<br>

<button onclick="fetch('/excited')">Excited</button>
<button onclick="fetch('/frightened')">Frightened</button>

</body>
</html>










)rawliteral";

namespace Website
{
    const char* getPage()
    {
        return MAIN_PAGE;
    }
}