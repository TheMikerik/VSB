import React, { useState } from 'react';
import { IonInput, IonButton, IonItem, IonLabel, IonTextarea, IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonButtons, IonMenuButton, IonAlert } from '@ionic/react';
import './AddSurvey.css';

const AddSurvey: React.FC = () => {
  const [title, setTitle] = useState('');
  const [description, setDescription] = useState('');
  const [estimatedTime, setEstimatedTime] = useState('');
  const [showSuccess, setShowSuccess] = useState(false);
  const [showError, setShowError] = useState(false);

  const handleClick = () => {

    if (!title || !description || !estimatedTime) {
      setShowError(true);
      return;
    }

    const survey = { title, description, estimatedTime };
    console.log(survey);

    fetch('http://localhost:8080/api/survey/add', {
      method: "POST",
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify(survey)
    }).then(response => {
      if (response.ok) {
        setTitle('');
        setDescription('');
        setEstimatedTime('');
        setShowSuccess(true);
        console.log("Survey added");
      } else {
        console.error('Failed to add survey');
      }
    }).catch(error => {
      console.error('Error adding survey:', error);
    });


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
      <IonAlert
        isOpen={showSuccess}
        onDidDismiss={() => setShowSuccess(false)}
        header="Success"
        message="Survey was added."
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

export default AddSurvey;
