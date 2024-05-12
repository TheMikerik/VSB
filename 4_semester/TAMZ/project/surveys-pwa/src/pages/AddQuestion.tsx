import React, { useState } from 'react';
import { IonInput, IonButton, IonItem, IonLabel, IonTextarea, IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonButtons, IonMenuButton } from '@ionic/react';
import './AddQuestion.css';

const AddQuestion: React.FC = () => {
  const [id, setId] = useState('');
  const [type, setType] = useState('');
  const [label, setLabel] = useState('');
  const [options, setOptions] = useState('');

  const url = 'http://localhost:8080/api/questions/add/' + id;

  const handleClick = () => {
    const question = { type, label, options };
    console.log(question);

    fetch(url, {
      method: "POST",
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(question)
    }).then(() => {
      console.log('Question added')
    })
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
            <IonLabel position="stacked">Id</IonLabel>
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
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Options</IonLabel>
            <IonInput className='cus-ion-input' type="text" value={options} onIonChange={e => setOptions(e.detail.value!)} />
          </IonItem>
          <IonButton onClick={handleClick} expand="full">Submit</IonButton>
        </form>
      </IonContent>
    </IonPage>
  );
};

export default AddQuestion;
