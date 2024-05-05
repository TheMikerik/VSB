import { IonAlert, IonApp, IonHeader, IonToolbar, IonTitle, IonContent, IonGrid, IonRow, IonCol, IonItem, IonLabel, IonInput } from "@ionic/react";
import React, { useRef, useState } from "react";
import BmiControls from "../components/BmiControls";
import BmiResult from "../components/BmiResult";

const TestPage: React.FC = () => {
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

export default TestPage;