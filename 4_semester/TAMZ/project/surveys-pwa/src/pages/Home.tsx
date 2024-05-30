import React, { useState, useEffect } from 'react';
import { IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonCard, IonCardContent, IonCardHeader, IonButton, IonItem, IonGrid, IonRow, IonCol, IonIcon, IonButtons, IonMenuButton } from '@ionic/react';
import './Home.css';

import { hourglassOutline, caretForwardOutline } from 'ionicons/icons';
import SurveyInt from '../interfaces/_survey';

const Home: React.FC = () => {

  const [surveys, setSurveys] = useState<SurveyInt[]>([]);

  useEffect(() => {
    if (!localStorage.getItem('survStarted')) {
      localStorage.setItem('survStarted', '0');
    }

    if (!localStorage.getItem('survFinished')) {
      localStorage.setItem('survFinished', '0');
    }

    if (!localStorage.getItem('timeSpent')) {
      localStorage.setItem('timeSpent', '0');
    }

    fetch("http://localhost:8080/api/survey/getAll")
      .then(res => res.json())
      .then((result) => {
        setSurveys(result);
      })
  }, []);

  const startSurvey = (estimatedTime: number) => {
    const survStarted = parseInt(localStorage.getItem('survStarted') || '0', 10) + 1;
    localStorage.setItem('survStarted', survStarted.toString());

    saveTimeSpent(estimatedTime);
  };

  const saveTimeSpent = (estimatedTime: number) => {
    const timeSpent = parseInt(localStorage.getItem('timeSpent') || '0', 10) + estimatedTime;
    localStorage.setItem('timeSpent', timeSpent.toString());
  };


  return (
    <IonPage>
      <IonHeader>
        <IonToolbar className='toolbar'>
          <IonButtons slot="start">
            <IonMenuButton style={{ "--color": "var(--ion-background)" }}></IonMenuButton>
          </IonButtons>
          <IonTitle className='app-title'>Surveys PWA</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent fullscreen scrollY={true} className="ion-padding">
        {surveys.map(survey => (
          <IonCard key={survey.id} className="survey-card">
            <IonCardHeader className="survey-card-header">
              <IonTitle>{survey.title}</IonTitle>
            </IonCardHeader>
            <IonCardContent className="survey-card-content">
              <IonGrid>
                <IonRow className="center-row">
                  <IonItem lines="full" className='description-box'>
                    <p className="survey-description">{survey.description}</p>
                  </IonItem>
                </IonRow>
                <IonRow>
                  <IonCol className='ion-text-left'>
                    <IonButton expand='block' className='take-survey-button'>
                      <IonIcon slot="start" icon={hourglassOutline} />
                      <p className="button-text">{survey.estimatedTime}</p>
                    </IonButton>
                  </IonCol>
                  <IonCol>
                    <IonButton onClick={() => startSurvey(parseInt(survey.estimatedTime, 10))} routerLink={`/survey/${survey.id}`} expand="block" className="take-survey-button">
                      <IonIcon slot="start" icon={caretForwardOutline} />
                      Start
                    </IonButton>
                  </IonCol>
                </IonRow>
              </IonGrid>
            </IonCardContent>
          </IonCard>
        ))}
      </IonContent>
    </IonPage>
  );
};

export default Home;