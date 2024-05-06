import React from 'react';
import { IonRow, IonCol, IonButton, IonIcon } from '@ionic/react';
import { arrowUpCircleOutline } from 'ionicons/icons';

const BmiControls: React.FC<{
    onCalculate: () => void;
    onReset: () => void;
}> = props => {
    return (
        <IonRow>
            <IonCol className='ion-text-left'>
                <IonButton onClick={props.onCalculate}>
                    <IonIcon slot='start' icon={arrowUpCircleOutline} />
                    calculate
                </IonButton>
            </IonCol>
            <IonCol className='ion-text-right'>
                <IonButton onClick={props.onReset}>
                    <IonIcon slot='start' icon={arrowUpCircleOutline} />
                    restart
                </IonButton>
            </IonCol>
        </IonRow>
    );
}

export default BmiControls;