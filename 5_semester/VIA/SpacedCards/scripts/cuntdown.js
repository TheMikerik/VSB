const targetDate = new Date("Dec 31, 2024 00:00:00").getTime(); // Set your target date here

const countdownInterval = setInterval(function() {
    const now = new Date().getTime();
    const timeLeft = targetDate - now;

    // Time calculations for days, hours, minutes, and seconds
    const days = Math.floor(timeLeft / (1000 * 60 * 60 * 24));
    const hours = Math.floor((timeLeft % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
    const minutes = Math.floor((timeLeft % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((timeLeft % (1000 * 60)) / 1000);

    // Display the countdown in the countdown div
    document.getElementById("countdown").innerHTML = 
        days + "d " + hours + "h " + minutes + "m " + seconds + "s ";

    // If the countdown is finished, display a message
    if (timeLeft < 0) {
        clearInterval(countdownInterval);
        document.getElementById("countdown").innerHTML = "EXPIRED";
    }
}, 1000);
