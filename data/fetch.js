const soundText = document.getElementById("sound_value");
const pirText = document.getElementById("pir_value");

const fetchData = async () => {
    const pirData = fetch("/data/pir").then(async (data) => await data.json());
    const soundData = fetch("/data/sound").then(async (data) => await data.json());

    return pirData, soundData;
}

setInterval(() => fetchData(), 1000);
pirText.innerHTML = pirData;
soundText.innerHTML = soundData;