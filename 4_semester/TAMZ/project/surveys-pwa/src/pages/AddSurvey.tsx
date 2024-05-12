import React, { useState } from 'react';
import { IonInput, IonButton, IonItem, IonLabel, IonTextarea, IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonButtons, IonMenuButton } from '@ionic/react';
import './AddSurvey.css';

const AddSurvey: React.FC = () => {
  const [title, setTitle] = useState('');
  const [description, setDescription] = useState('');
  const [estimatedTime, setEstimatedTime] = useState('');

  const handleClick = () => {
    const survey = { title, description, estimatedTime };
    console.log(survey);

    fetch('http://localhost:8080/api/survey/add', {
      method: "POST",
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(survey)
    }).then(() => {
      console.log('Survey added')
    })
  };

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar className='toolbar'>
          <IonButtons slot="start">
            <IonMenuButton style={{ "--color": "var(--ion-background-light)" }}></IonMenuButton>
          </IonButtons>
          <IonTitle className='app-title'>Add Survey</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent className='cus-ion-content'>
        <form className='cus-form'>
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Title</IonLabel>
            <IonInput className='cus-ion-input' type="text" value={title} onIonChange={e => setTitle(e.detail.value!)} />
          </IonItem>
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Description</IonLabel>
            <IonTextarea className='cus-ion-textarea' value={description} onIonChange={e => setDescription(e.detail.value!)} />
          </IonItem>
          <IonItem className='cus-ion-item'>
            <IonLabel position="stacked">Estimated Time</IonLabel>
            <IonInput className='cus-ion-input' type="text" value={estimatedTime} onIonChange={e => setEstimatedTime(e.detail.value!)} />
          </IonItem>
          <IonButton onClick={handleClick} expand="full">Submit</IonButton>
        </form>
      </IonContent>
    </IonPage>
  );
};

export default AddSurvey;
