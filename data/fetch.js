const soundText = document.getElementById("sound_value");
const pirText = document.getElementById("pir_value");

setInterval(() => {
    fetch("/data/pir").then(res => res.json()).then(data => {
        console.log(data);
        pirText.textContent = data.value;
    })

    fetch("/data/sound").then(res => res.json()).then(data => {
        console.log(data);
        soundText.textContent = data.value;
    })
}, 1000);