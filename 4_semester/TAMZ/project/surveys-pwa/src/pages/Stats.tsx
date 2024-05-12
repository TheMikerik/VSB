import React from 'react';
import { IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonCard, IonCardContent, IonCardHeader, IonGrid, IonRow, IonCol, IonButton, IonIcon, IonButtons, IonMenuButton } from '@ionic/react';

import './Stats.css';
import { downloadOutline } from 'ionicons/icons';

const StatisticsPage: React.FC = () => {

    const survStarted = localStorage.getItem('survStarted') || '0';
    const survFinished = localStorage.getItem('survFinished') || '0';
    const timeSpent = localStorage.getItem('timeSpent') || '0';

    const handleDownloadStats = () => {
        const data = [
            ['Statistic', 'Value'],
            ['Surveys Started', survStarted],
            ['Surveys Finished', survFinished],
            ['Time Spent (mins)', timeSpent]
        ];

        const csvContent = data.map(row => row.join(',')).join('\n');

        const blob = new Blob([csvContent], { type: 'text/csv' });

        const anchor = document.createElement('a');
        anchor.href = window.URL.createObjectURL(blob);
        anchor.download = 'survey_stats.csv';

        document.body.appendChild(anchor);
        anchor.click();

        document.body.removeChild(anchor);
    };

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar className='toolbar'>
                    <IonButtons slot="start">
                        <IonMenuButton style={{ "--color": "var(--ion-background-light)" }}></IonMenuButton>
                    </IonButtons>
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
                                        <h2 className='stat-text'>
                                            {survStarted} pcs
                                        </h2>
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
                                        Time Spent
                                    </IonCardHeader>
                                    <IonCardContent>
                                        <h2 className='stat-text'>
                                            {timeSpent} mins
                                        </h2>
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
                                        <h2 className='stat-text'>
                                            {survFinished} pcs
                                        </h2>
                                    </IonCardContent>
                                </IonCard>
                            </div>
                        </IonCol>
                    </IonRow>
                    <IonRow>
                        <IonCol>
                            <div className="button-container">
                                <IonButton onClick={handleDownloadStats} expand="block" className='testbuton'>
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
