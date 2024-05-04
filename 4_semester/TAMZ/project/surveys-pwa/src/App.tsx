import React, { useRef, useState } from 'react';
import { Redirect, Route } from 'react-router-dom';
import { IonApp, IonGrid, IonHeader, IonContent, IonTitle, IonToolbar, setupIonicReact, IonRow, IonCol, IonItem, IonLabel, IonAlert, IonInput } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';
import Home from './pages/Home';
import BmiControls from './components/BmiControls';
import BmiResult from './components/BmiResult';

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
import '@ionic/react/css/palettes/dark.system.css';

/* Theme variables */
import './theme/variables.css';

setupIonicReact();

const App: React.FC = () => {
  const weightInputRef = useRef<HTMLIonInputElement>(null);
  const hieghtInputRef = useRef<HTMLIonInputElement>(null);

  const [calculatedBMI, setCalculatedBmi] = useState<number>();
  const [error, setError] = useState<string>();

  const calculateBMI = () => {
    const enteredWeight = weightInputRef.current!.value;
    const enteredHeight = hieghtInputRef.current!.value;

    if (!enteredWeight || !enteredHeight) {
      return;
    }

    if (
      !enteredHeight ||
      !enteredWeight ||
      +enteredHeight <= 0 ||
      +enteredWeight <= 0
    ) {
      setError('Please enter a valid (non-negative) input number');
      return;
    }

    const bmi = +enteredWeight / (+enteredHeight * +enteredHeight);

    setCalculatedBmi(bmi);
  };

  const resetInputs = () => {
    weightInputRef.current!.value = '';
    hieghtInputRef.current!.value = '';
  }

  const clearError = () => {
    setError('');
  }

  return (
    <React.Fragment>
      <IonAlert
        isOpen={!!error}
        message={error}
        buttons={[{
          text: 'Okay', handler: clearError => {

          }
        }]}
      />
      <IonApp>
        <IonHeader>
          <IonToolbar color="primary">
            <IonTitle>Surveys</IonTitle>
          </IonToolbar>
        </IonHeader>
        <IonContent className='ion-padding'>
          <IonGrid>
            <IonRow>
              <IonCol>
                <IonItem>
                  <IonLabel position="stacked">Your height</IonLabel>
                  <IonInput type="number" ref={hieghtInputRef}></IonInput>
                </IonItem>
              </IonCol>
            </IonRow>
            <IonRow>
              <IonCol>
                <IonItem>
                  <IonLabel position="stacked">Your weight</IonLabel>
                  <IonInput type="number" ref={weightInputRef}></IonInput>
                </IonItem>
              </IonCol>
            </IonRow>
            <BmiControls onCalculate={calculateBMI} onReset={resetInputs} />
            {calculatedBMI && (
              <BmiResult result={calculatedBMI} />

            )}
          </IonGrid>
        </IonContent>
      </IonApp>
    </React.Fragment>
  );
};


// <IonApp>
//   <IonReactRouter>
//     <IonRouterOutlet>
//       <Route exact path="/home">
//         <Home />
//       </Route>
//       <Route exact path="/">
//         <Redirect to="/home" />
//       </Route>
//     </IonRouterOutlet>
//   </IonReactRouter>
// </IonApp>

export default App;
