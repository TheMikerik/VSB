import React, { useState, useEffect } from 'react';
import { IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonCard, IonCardContent, IonCardHeader, IonButton, IonItem, IonGrid, IonRow, IonCol, IonIcon } from '@ionic/react';
import './Home.css';

import { hourglassOutline, caretForwardOutline } from 'ionicons/icons';

const Home: React.FC = () => {
  // const [surveys, setSurveys] = useState<any[]>([]);

  // useEffect(() => { 
  //   fetch('path/to/your/surveys.json')
  //     .then(response => response.json())
  //     .then(data => setSurveys(data))
  //     .catch(error => console.error('Error fetching surveys:', error));
  // }, []);

  const [surveys] = useState([
    {
      title: "Customer Satisfaction Survey",
      description: "Tell us about your experience with our products and services.",
      estimatedTime: "5 minutes",
      id: 1,
    },
    {
      title: "Market Research Survey",
      description: "Help us understand your preferences and needs.",
      estimatedTime: "10 minutes",
      id: 2,
    },
    {
      title: "Website Usability Survey",
      description: "Share your feedback on the ease of use of our website.",
      estimatedTime: "7 minutes",
      id: 3,
    },
    {
      title: "Product Feedback Survey",
      description: "Provide your insights on a specific product.",
      estimatedTime: "8 minutes",
      id: 4,
    },
    {
      title: "Event Satisfaction Survey",
      description: "Let us know what you thought of our recent event.",
      estimatedTime: "3 minutes",
      id: 5,
    },
    {
      title: "Brand Perception Survey",
      description: "Help us understand your perception of our brand.",
      estimatedTime: "12 minutes",
      id: 6,
    },
    {
      title: "Employee Satisfaction Survey",
      description: "Share your thoughts on your work experience.",
      estimatedTime: "15 minutes",
      id: 7,
    },
    {
      title: "Feature Request Survey",
      description: "Suggest new features you'd like to see.",
      estimatedTime: "10 minutes",
      id: 8,
    },
    {
      title: "App Usability Survey",
      description: "Provide feedback on the usability of our mobile app.",
      estimatedTime: "8 minutes",
      id: 9,
    },
    {
      title: "Competition Analysis Survey",
      description: "Help us understand our competitors better.",
      estimatedTime: "10 minutes",
      id: 10,
    },
  ]);

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar className='toolbar'>
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
                    <IonButton routerLink={`/survey/${survey.id}`} expand="block" className="take-survey-button">
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
