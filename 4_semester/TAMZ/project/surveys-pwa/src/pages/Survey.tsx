import { IonPage, IonHeader, IonToolbar, IonTitle, IonContent, IonInput, IonSelect, IonSelectOption, IonRadioGroup, IonRadio, IonButton, IonLabel, IonItem, IonList, IonCard, IonGrid, IonRow, IonCol, IonTextarea, IonButtons, IonMenuButton } from '@ionic/react';
import React, { useState, useEffect } from 'react';
import { useParams } from 'react-router-dom';
import './Survey.css';
import SurveyInt from '../interfaces/_survey';

const SurveyPage: React.FC = () => {
  const [survey, setSurvey] = useState<SurveyInt | null>(null);
  const { id } = useParams<{ id: string }>();

  useEffect(() => {
    fetch(`http://localhost:8080/api/survey/get/${id}`)
      .then(res => res.json())
      .then((result: SurveyInt) => {
        const promises = result.questions.map(question =>
          fetch(`http://localhost:8080/api/option/getAll/${question.id}`)
            .then(res => res.json())
            .then(options => ({ ...question, options }))
        );
        Promise.all(promises)
          .then(questionsWithOptions => {
            setSurvey({ ...result, questions: questionsWithOptions });
          })
          .catch(error => {
            console.error('Error fetching options:', error);
          });
      })
      .catch(error => {
        console.error('Error fetching survey data:', error);
      });

    console.log(survey);
  }, [id]);

  if (!survey) {
    return <div>Loading...</div>;
  }

  const finishSurvey = () => {
    const survFinished = parseInt(localStorage.getItem('survFinished') || '0', 10) + 1;
    localStorage.setItem('survFinished', survFinished.toString());
  };

  return (
    <IonPage>
      <IonHeader>
        <IonToolbar className='toolbar'>
          <IonButtons slot="start">
            <IonMenuButton style={{ "--color": "var(--ion-background-light)" }}></IonMenuButton>
          </IonButtons>
          <IonTitle className='app-title'>Survey</IonTitle>
        </IonToolbar>
      </IonHeader>
      <IonContent>
        <h1 className='sur-title margin'>{survey.title}</h1>
        <p className='sur-desc margin'>{survey.description}</p>
        <form className='margin'>
          {survey.questions.map((question, index) => (
            <IonCard key={index} className='card-styling'>
              <IonGrid>
                <IonRow>
                  <IonLabel className='card-label'>{index + 1}.</IonLabel>
                </IonRow>
                <IonRow>
                  <IonLabel className='card-question'>{question.label}</IonLabel>
                </IonRow>
              </IonGrid>


              {/* TEXT INPUT */}
              {question.type === 'text' && (
                <IonTextarea className='answer-section' placeholder='Write your answer here...' />
              )}


              {/* MULTIPLE CHOICE */}
              {question.type === 'multiple_choice' && (
                <IonRow className='multiple-answer-section'>
                  <IonSelect multiple placeholder='Select multiple answers...'>
                    {question.options?.map((option, optionIndex) => (
                      <IonSelectOption key={optionIndex} value={option}>{option.option}</IonSelectOption>
                    ))}
                  </IonSelect>
                </IonRow>
              )}


              {/* SINGLE CHOICE */}
              {question.type === 'single_choice' && (
                <IonRadioGroup className="custom-radio">
                  {question.options?.map((option, optionIndex) => (
                    <IonItem key={optionIndex} className="custom-radio">
                      <IonRadio slot="start" value={option} />
                      <IonLabel className='label-text'>{option.option}</IonLabel>
                    </IonItem>
                  ))}
                </IonRadioGroup>
              )}

            </IonCard>
          ))}

          <IonButton onClick={finishSurvey} type="submit" className='survey-send-button'>Finish survey</IonButton>
        </form>
      </IonContent>
    </IonPage>
  );
};

export default SurveyPage;
