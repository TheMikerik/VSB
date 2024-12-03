document.querySelector('.contact-form').addEventListener('submit', function (event) {
    // Prevent form submission
    event.preventDefault();

    // Clear previous error messages
    const errorMessages = document.querySelectorAll('.error-message');
    errorMessages.forEach(msg => msg.classList.remove('visible'));

    // Get form fields
    const name = document.getElementById('name').value.trim();
    const email = document.getElementById('email').value.trim();
    const message = document.getElementById('message').value.trim();

    let isValid = true;

    // Validate Name
    if (name.length < 2) {
        const nameError = document.querySelector('#name + .error-message');
        nameError.textContent = 'Name must be at least 2 characters.';
        nameError.classList.add('visible');
        isValid = false;
    }

    // Validate Email
    if (!email) {
        const emailError = document.querySelector('#email + .error-message');
        emailError.textContent = 'Email is required.';
        emailError.classList.add('visible');
        isValid = false;
    } else if (!/\S+@\S+\.\S+/.test(email)) {
        const emailError = document.querySelector('#email + .error-message');
        emailError.textContent = 'Invalid email address.';
        emailError.classList.add('visible');
        isValid = false;
    }

    // Validate Message
    if (message.length < 10) {
        const messageError = document.querySelector('#message + .error-message');
        messageError.textContent = 'Message must be at least 10 characters.';
        messageError.classList.add('visible');
        isValid = false;
    }

    // Submit the form if all fields are valid
    if (isValid) {
        alert('Message sent successfully!');
        this.submit(); // Optional: Use if connected to backend
    }
});