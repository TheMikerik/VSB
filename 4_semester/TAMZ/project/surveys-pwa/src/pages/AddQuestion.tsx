import React, { useState } from 'react';
import { IonInput, IonButton, IonItem, IonLabel, IonTextarea, IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonButtons, IonMenuButton, IonAlert } from '@ionic/react';
import './AddQuestion.css';

const AddQuestion: React.FC = () => {
  const [id, setId] = useState('');
  const [type, setType] = useState('');
  const [label, setLabel] = useState('');
  const [showSuccess, setShowSuccess] = useState(false);
  const [showError, setShowError] = useState(false);

  const url = 'http://localhost:8080/api/questions/add/' + id;

  const handleClick = () => {

    if (!id || !type || !label) {
      setShowError(true);
      return;
    }

    const question = { type, label };
    console.log(question);

    fetch(url, {
      method: "POST",
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(question)
    }).then(response => {
      if (response.ok) {
        setType('');
        setLabel('');
        setShowSuccess(true);
        console.log("Question added");
      } else {
        console.error('Failed to add question');
      }
    }).catch(error => {
      console.error('Error adding question:', error);
    });
  };

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar className='toolbar'>
          <IonButtons slot="start">
            <IonMenuButton style={{ "--color": "var(--ion-background-light)" }}></IonMenuButton>
          </IonButtons>
          <IonTitle className='app-title'>Add Question</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent className='cus-ion-content'>
        <form className='cus-form'>
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Survey Id</IonLabel>
            <IonInput className='cus-ion-input' type="text" value={id} onIonChange={e => setId(e.detail.value!)} />
          </IonItem>
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Type - text, single_choice, multiple_choice</IonLabel>
            <IonInput className='cus-ion-input' type="text" value={type} onIonChange={e => setType(e.detail.value!)} />
          </IonItem>
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Label</IonLabel>
            <IonTextarea className='cus-ion-textarea' value={label} onIonChange={e => setLabel(e.detail.value!)} />
          </IonItem>
          <IonButton onClick={handleClick} expand="full">Submit</IonButton>
        </form>
      </IonContent>
      <IonAlert
        isOpen={showSuccess}
        onDidDismiss={() => setShowSuccess(false)}
        header="Success"
        message="Question was added."
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

export default AddQuestion;
