import React, { useState } from 'react';
import { IonInput, IonButton, IonItem, IonLabel, IonTextarea, IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonButtons, IonMenuButton, IonAlert } from '@ionic/react';
import './AddQuestion.css';

const AddOption: React.FC = () => {
  const [id, setId] = useState('');
  const [options, setOptions] = useState('');
  const [showSuccess, setShowSuccess] = useState(false);
  const [showError, setShowError] = useState(false);

  const url = 'http://localhost:8080/api/option/add/' + id;

  const handleClick = () => {

    if (!id || !options) {
      setShowError(true);
      return;
    }

    const option = { option: options };
    console.log(option);

    fetch(url, {
      method: "POST",
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(option)
    }).then(response => {
      if (response.ok) {
        setOptions('');
        setShowSuccess(true);
        console.log("Option added");
      } else {
        console.error('Failed to add option');
      }
    }).catch(error => {
      console.error('Error adding option:', error);
    });
  };

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar className='toolbar'>
          <IonButtons slot="start">
            <IonMenuButton style={{ "--color": "var(--ion-background-light)" }}></IonMenuButton>
          </IonButtons>
          <IonTitle className='app-title'>Add Option</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent className='cus-ion-content'>
        <form className='cus-form'>
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Question Id</IonLabel>
            <IonInput className='cus-ion-input' type="text" value={id} onIonChange={e => setId(e.detail.value!)} />
          </IonItem>
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Option</IonLabel>
            <IonInput className='cus-ion-input' type="text" value={options} onIonChange={e => setOptions(e.detail.value!)} />
          </IonItem>
          <IonButton onClick={handleClick} expand="full">Submit</IonButton>
        </form>
      </IonContent>
      <IonAlert
        isOpen={showSuccess}
        onDidDismiss={() => setShowSuccess(false)}
        header="Success"
        message="Option was added."
        buttons={['OK']}
      />
      <IonAlert
        isOpen={showError}
        onDidDismiss={() => setShowError(false)}
        header="Error"
        message="Please fill in all the fields."
        buttons={['OK']}
      />
    </IonPage>
  );
};

export default AddOption;
