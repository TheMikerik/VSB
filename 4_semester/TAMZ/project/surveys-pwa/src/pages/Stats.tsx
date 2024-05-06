import React from 'react';
import { IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonCard, IonCardContent, IonCardHeader, IonGrid, IonRow, IonCol, IonButton, IonIcon } from '@ionic/react';

import './Stats.css';
import { downloadOutline } from 'ionicons/icons';

const StatisticsPage: React.FC = () => {
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar className='toolbar'>
                    <IonTitle className='app-title'>Statistics</IonTitle>
                </IonToolbar>
            </IonHeader>
            <IonContent fullscreen>
                <IonGrid>
                    <IonRow>
                        <IonCol size="12" size-md="4">
                            <div className="statistic-card">
                                <IonCard className="custom-ion-card">
                                    <IonCardHeader>
                                        Surveys Started
                                    </IonCardHeader>
                                    <IonCardContent>
                                        <h2 className='stat-text'>10</h2> {/* Static number */}
                                    </IonCardContent>
                                </IonCard>
                            </div>
                        </IonCol>
                    </IonRow>
                    <IonRow>
                        <IonCol size="12" size-md="4">
                            <div className="statistic-card">
                                <IonCard className="custom-ion-card">
                                    <IonCardHeader>
                                        Questions Answered
                                    </IonCardHeader>
                                    <IonCardContent>
                                        <h2 className='stat-text'>200</h2> {/* Static number */}
                                    </IonCardContent>
                                </IonCard>
                            </div>
                        </IonCol>
                    </IonRow>
                    <IonRow>
                        <IonCol size="12" size-md="4">
                            <div className="statistic-card">
                                <IonCard className="custom-ion-card">
                                    <IonCardHeader>
                                        Surveys Finished
                                    </IonCardHeader>
                                    <IonCardContent>
                                        <h2 className='stat-text'>50</h2> {/* Static number */}
                                    </IonCardContent>
                                </IonCard>
                            </div>
                        </IonCol>
                    </IonRow>
                    <IonRow>
                        <IonCol>
                            <div className="button-container">
                                <IonButton expand="block" className='testbuton'>
                                    <IonIcon slot="start" icon={downloadOutline} />
                                    Download Stats
                                </IonButton>
                            </div>
                        </IonCol>
                    </IonRow>
                </IonGrid>
            </IonContent>
        </IonPage>
    );
};

export default StatisticsPage;
