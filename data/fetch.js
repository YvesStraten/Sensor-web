const soundText = document.getElementById("sound_value");
const pirText = document.getElementById("pir_value");

setInterval(() => {
    fetch("/api/data").then(res => res.json()).then(data => {
        console.log(data);
        pirText.textContent = data.sensors.pir;
        soundText.textContent = data.sensors.sound;
    })

}, 1000);