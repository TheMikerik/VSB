import { Redirect, Route, } from 'react-router-dom';
import { IonApp, setupIonicReact, IonRouterOutlet, IonContent, IonItem, IonLabel, IonList, IonMenu, IonHeader, IonTitle, IonToolbar } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';
import Home from './pages/Home';


/* Core CSS required for Ionic components to work properly */
import '@ionic/react/css/core.css';

/* Basic CSS for apps built with Ionic */
import '@ionic/react/css/normalize.css';
import '@ionic/react/css/structure.css';
import '@ionic/react/css/typography.css';

/* Optional CSS utils that can be commented out */
import '@ionic/react/css/padding.css';
import '@ionic/react/css/float-elements.css';
import '@ionic/react/css/text-alignment.css';
import '@ionic/react/css/text-transformation.css';
import '@ionic/react/css/flex-utils.css';
import '@ionic/react/css/display.css';

/**
 * Ionic Dark Mode
 * -----------------------------------------------------
 * For more info, please see:
 * https://ionicframework.com/docs/theming/dark-mode
 */

/* import '@ionic/react/css/palettes/dark.always.css'; */
/* import '@ionic/react/css/palettes/dark.class.css'; */
// import '@ionic/react/css/palettes/dark.system.css';

/* Theme variables */
import './theme/variables.css';
import Stats from './pages/Stats';
import Survey from './pages/Survey';
import { useEffect, useState } from 'react';
import AddSurvey from './pages/AddSurvey';
import AddQuestion from './pages/AddQuestion';
import SurveyInt from './interfaces/_survey';
import AddOption from './pages/AddOption';

setupIonicReact();

const App: React.FC = () => {
  const [surveys, setSurveys] = useState<SurveyInt[]>([]);

  useEffect(() => {
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
    <IonApp>
      <IonReactRouter>
        <IonMenu contentId="main">
          <IonHeader>
            <IonToolbar style={{ "--background": "var(--primary)" }}>
              <IonTitle>Menu</IonTitle>
            </IonToolbar>
          </IonHeader>
          <IonContent>
            <IonList>
              <IonItem routerLink="/home">
                <IonLabel>Home</IonLabel>
              </IonItem>
              <IonItem routerLink="/stats">
                <IonLabel>Stats</IonLabel>
              </IonItem>
              <IonItem routerLink="/addSurvey">
                <IonLabel>Add Survey</IonLabel>
              </IonItem>
              <IonItem routerLink="/addQuestion">
                <IonLabel>Add Question</IonLabel>
              </IonItem>
              <IonItem routerLink="/addOption">
                <IonLabel>Add Option</IonLabel>
              </IonItem>
              <br />
              <br />
              <br />
              <br />
              <IonItem>Surveys:</IonItem>
              {surveys.map((survey) => (
                <IonItem key={survey.id} onClick={() => startSurvey(parseInt(survey.estimatedTime, 10))} routerLink={`/survey/${survey.id}`}>
                  <IonLabel>{survey.title}</IonLabel>
                </IonItem>
              ))}
            </IonList>
          </IonContent>
        </IonMenu>
        <IonRouterOutlet id="main">
          <Route exact path="/">
            <Redirect to="/home" />
          </Route>

          <Route exact path="/home">
            <Home />
          </Route>
          <Route exact path="/stats">
            <Stats />
          </Route>
          <Route exact path="/addSurvey">
            <AddSurvey />
          </Route>
          <Route exact path="/addQuestion">
            <AddQuestion />
          </Route>
          <Route exact path="/addOption">
            <AddOption />
          </Route>
          <Route path="/survey/:id">
            <Survey />
          </Route>
        </IonRouterOutlet>
      </IonReactRouter>
    </IonApp >
  );
};

export default App;
