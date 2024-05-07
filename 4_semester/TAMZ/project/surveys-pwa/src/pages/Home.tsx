import React, { useState, useEffect } from 'react';
import { IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonCard, IonCardContent, IonCardHeader, IonButton, IonItem, IonGrid, IonRow, IonCol, IonIcon } from '@ionic/react';
import './Home.css';

import { hourglassOutline, caretForwardOutline } from 'ionicons/icons';

const Home: React.FC = () => {

  const [surveys] = useState([
    {
      "title": "Movie Magic!",
      "description": "Tell us about your favorite films!",
      "estimatedTime": "2 minutes",
      "id": "1",
      "questions": [
        {
          "type": "text",
          "label": "What's your favorite genre of movie?"
        },
        {
          "type": "multiple_choice",
          "label": "How often do you watch movies at home?",
          "options": ["Daily", "Several times a week", "Once a week", "Less than once a week"]
        },
        {
          "type": "single_choice",
          "label": "Would you recommend our movie streaming service to a friend?",
          "options": ["Yes", "No", "Unsure"]
        }
      ]
    },
    {
      "title": "Coffee Break!",
      "description": "Help us understand your coffee habits!",
      "estimatedTime": "4 minutes",
      "id": "2",
      "questions": [
        {
          "type": "multiple_choice",
          "label": "How do you typically drink your coffee?",
          "options": ["Black", "With milk/creamer", "With sugar/sweetener", "Flavored Coffee"]
        },
        {
          "type": "text",
          "label": "What's your favorite brand of coffee?"
        },
        {
          "type": "single_choice",
          "label": "Do you prefer hot or iced coffee?",
          "options": ["Hot", "Iced", "Both"]
        },
        {
          "type": "multiple_choice",
          "label": "What time of day do you usually drink coffee?",
          "options": ["Morning", "Afternoon", "Both", "Never"]
        },
        {
          "type": "number",
          "label": "On average, how many cups of coffee do you drink per day?"
        },
        {
          "type": "single_choice",
          "label": "Do you consider yourself a coffee addict?",
          "options": ["Yes", "No", "Maybe"]
        },
        {
          "type": "text",
          "label": "What are your favorite coffee shop recommendations?"
        }
      ]
    },
    {
      "title": "Wanderlust Survey",
      "description": "Share your travel dreams and experiences!",
      "estimatedTime": "8 minutes",
      "id": "4",
      "questions": [
        {
          "type": "multiple_choice",
          "label": "What type of travel experience do you prefer?",
          "options": ["Relaxation on the beach", "Adventure and exploration", "Cultural immersion", "City breaks", "Luxury getaways"]
        },
        {
          "type": "text",
          "label": "What is your dream travel destination?"
        },
        {
          "type": "multiple_choice",
          "label": "When do you typically travel (time of year)?",
          "options": ["Spring", "Summer", "Fall", "Winter", "All year round"]
        },
        {
          "type": "number",
          "label": "How much do you typically budget for a vacation?"
        },
        {
          "type": "single_choice",
          "label": "Do you prefer to travel solo or with others?",
          "options": ["Solo", "With family", "With friends", "Both"]
        },
        {
          "type": "multiple_choice",
          "label": "What amenities are most important to you in a hotel?",
          "options": ["Location", "Price", "Amenities (pool, gym, etc.)", "Luxury accommodations", "Unique experiences"]
        },
        {
          "type": "text",
          "label": "What are your top 3 travel essentials?"
        },
        {
          "type": "single_choice",
          "label": "Have you ever used a travel booking app or website?",
          "options": ["Yes", "No"]
        },
        {
          "type": "text",
          "label": "If so, which travel booking app or website do you prefer?"
        },
        {
          "type": "single_choice",
          "label": "How important is eco-friendly travel to you?",
          "options": ["Very important", "Somewhat important", "Not important"]
        },
        {
          "type": "text",
          "label": "Describe a travel experience that stands out to you the most. Why was it memorable?"
        },
        {
          "type": "multiple_choice",
          "label": "What travel styles are you most interested in trying in the future?",
          "options": ["Backpacking", "Volunteering abroad", "Culinary tours", "Road trips", "Luxury cruises"]
        },
        {
          "type": "text",
          "label": "What are some challenges you face when planning or taking trips?"
        },
        {
          "type": "text",
          "label": "What are your top travel tips for others?"
        },
        {
          "type": "text",
          "label": "Anything else you'd like to share about your travel experiences or preferences?"
        }
      ]
    }
  ]);

  // const [surveys, setSurveys] = useState<Survey[]>([]);

  // useEffect(() => {
  //   console.log('Fetching surveys...');

  //   fetch('../resources/surveys.json')
  //     .then(response => {
  //       console.log('Response received:', response);
  //       return response.json();
  //     })
  //     .then(data => {
  //       console.log('Data received:', data);
  //       setSurveys(data);
  //     })
  //     .catch(error => {
  //       console.error('Error fetching surveys:', error);
  //     });
  // }, []);


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








// const [surveys, setSurveys] = useState<any[]>([]);

// useEffect(() => {
//   fetch('path/to/your/surveys.json')
//     .then(response => response.json())
//     .then(data => setSurveys(data))
//     .catch(error => console.error('Error fetching surveys:', error));
// }, []);