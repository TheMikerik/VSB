const thumbnails = document.querySelectorAll('.gallery-thumbnail');
    const modal = document.getElementById('image-modal');
    const modalImage = document.getElementById('modal-image');
    const caption = document.getElementById('caption');
    const closeModal = document.querySelector('.close');

    thumbnails.forEach(thumbnail => {
        thumbnail.addEventListener('click', () => {
            modal.style.display = 'block';
            modalImage.src = thumbnail.src; // Set the clicked image as modal content
            caption.textContent = thumbnail.alt; // Set the alt text as caption
        });
    });

    closeModal.addEventListener('click', () => {
        modal.style.display = 'none';
    });

    // Close modal when clicking outside the image
    window.addEventListener('click', (e) => {
        if (e.target === modal) {
            modal.style.display = 'none';
        }
    });