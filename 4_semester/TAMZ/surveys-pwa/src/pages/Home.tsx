import React, { useState, useEffect } from 'react';
import { IonContent, IonHeader, IonPage, IonTitle, IonToolbar, IonCard, IonCardContent, IonCardHeader, IonButton, IonItem, IonGrid, IonRow, IonCol, IonIcon, IonButtons, IonMenuButton } from '@ionic/react';
import './Home.css';

import { hourglassOutline, caretForwardOutline } from 'ionicons/icons';

const Home: React.FC = () => {

  const [surveys] = useState([
    {
      "title": "Programming Languages ",
      "description": "Share your thoughts on programming languages!",
      "estimatedTime": "3 minutes",
      "id": "1",
      "questions": [
        {
          "type": "multiple_choice",
          "label": "Which programming language do you use most frequently?",
          "options": ["Python", "JavaScript", "Java", "C++", "Other (please specify)"]
        },
        {
          "type": "text",
          "label": "What factors do you consider most important when choosing a programming language for a new project?"
        },
        {
          "type": "single_choice",
          "label": "Do you prefer working with strongly typed or dynamically typed languages?",
          "options": ["Strongly typed", "Dynamically typed", "No preference"]
        },
        {
          "type": "multiple_choice",
          "label": "Which programming language are you most interested in learning next?",
          "options": ["Go", "Rust", "Kotlin", "Swift", "None"]
        },
        {
          "type": "text",
          "label": "What do you enjoy most about programming?"
        }
      ]
    },
    {
      "title": "Web Development",
      "description": "Share your insights on the future of web development!",
      "estimatedTime": "5 minutes",
      "id": "2",
      "questions": [
        {
          "type": "multiple_choice",
          "label": "Which web development framework do you use most often?",
          "options": ["React", "Angular", "Vue.js", "Other (please specify)", "None"]
        },
        {
          "type": "single_choice",
          "label": "What is the biggest challenge you face when developing websites?",
          "options": ["Keeping up with rapidly changing technologies", "Ensuring website responsiveness across all devices", "Balancing security with user experience", "Meeting tight deadlines", "Other (please specify)"]
        },
        {
          "type": "text",
          "label": "What are your thoughts on the importance of progressive web applications (PWAs) in the future of web development?"
        },
        {
          "type": "multiple_choice",
          "label": "Which front-end development skill do you consider most crucial for success?",
          "options": ["JavaScript (including frameworks)", "HTML and CSS", "Version control (e.g., Git)", "Understanding design principles", "All of the above"]
        },
        {
          "type": "text",
          "label": "What excites you most about the future of web development?"
        }
      ]
    },
    {
      "title": "Cybersecurity Awareness Survey",
      "description": "Test your cybersecurity knowledge and help us improve our training!",
      "estimatedTime": "5 minutes",
      "id": "3",
      "questions": [
        {
          "type": "multiple_choice",
          "label": "Which of the following is NOT a strong password practice?",
          "options": ["Using a mix of uppercase and lowercase letters, numbers, and symbols", "Using the same password for multiple accounts", "Changing your passwords regularly", "Using a password manager", "All of the above are strong practices"]
        },
        {
          "type": "single_choice",
          "label": "You receive an email from an unknown sender claiming to be from your bank. The email looks legitimate and asks you to confirm your account information by clicking on a link. What should you do?",
          "options": ["Click on the link and enter your information", "Forward the email to your bank's official email address", "Delete the email without opening it"]
        },
        {
          "type": "text",
          "label": "What are some red flags you look for when identifying potential phishing emails?"
        },
        {
          "type": "multiple_choice",
          "label": "How often do you back up your important data?",
          "options": ["Daily", "Weekly", "Monthly", "Less frequently than monthly", "Never"]
        },
        {
          "type": "single_choice",
          "label": "When browsing the internet, what security measures do you take to protect your device from malware?",
        },
        {
          "type": "text",
          "label": "What are some ways you stay informed about the latest cybersecurity threats?"
        },
        {
          "type": "single_choice",
          "label": "How confident are you in your ability to identify and avoid cyberattacks?",
          "options": ["Very confident", "Somewhat confident", "Neutral", "Somewhat unsure", "Not confident at all"]
        },
        {
          "type": "text",
          "label": "Do you have any suggestions for improving cybersecurity awareness training within your organization?"
        }
      ]
    },
    {
      "title": "Coding Challenges Survey",
      "description": "Share your experiences and preferences for coding challenges!",
      "estimatedTime": "4 minutes",
      "id": "4",
      "questions": [
        {
          "type": "multiple_choice",
          "label": "How often do you participate in coding challenges (e.g., LeetCode, HackerRank)?",
          "options": ["Daily", "Several times a week", "Once a week", "Less than once a week", "Never"]
        },
        {
          "type": "single_choice",
          "label": "What is your primary motivation for participating in coding challenges?",
          "options": ["Improving your problem-solving skills", "Learning new algorithms and data structures", "Preparing for technical interviews", "All of the above", "Other (please specify)"]
        },
        {
          "type": "text",
          "label": "Do you find coding challenges to be a valuable tool in your professional development?"
        },
        {
          "type": "multiple_choice",
          "label": "What type of coding challenges do you find most enjoyable?",
          "options": ["Algorithmic problems", "Logic puzzles", "Front-end development challenges", "Full-stack development challenges", "All of the above"]
        },
        {
          "type": "single_choice",
          "label": "Would you prefer coding challenges to be focused on real-world scenarios or more theoretical concepts?",
          "options": ["Real-world scenarios", "Theoretical concepts", "A balance of both"]
        },
        {
          "type": "text",
          "label": "What are some challenges you've faced when participating in coding challenges?"
        },
        {
          "type": "single_choice",
          "label": "Do you believe online coding challenges can accurately assess a developer's skills?",
          "options": ["Yes", "No", "It depends on the type of challenge"]
        },
        {
          "type": "text",
          "label": "What improvements would you suggest for online coding challenge platforms?"
        }
      ]
    },
    {
      "title": "Cloud Computing Adoption Survey",
      "description": "Share your insights on your organization's use of cloud computing!",
      "estimatedTime": "7 minutes",
      "id": "5",
      "questions": [
        {
          "type": "single_choice",
          "label": "Has your organization adopted cloud computing services?",
          "options": ["Yes", "No", "We are in the process of implementing cloud computing"]
        },
        {
          "type": "multiple_choice",
          "label": "If yes, which cloud computing services do you primarily use?",
          "options": ["Infrastructure as a Service (IaaS)", "Platform as a Service (PaaS)", "Software as a Service (SaaS)", "A combination of the above", "Not applicable"]
        },
        {
          "type": "text",
          "label": "What are the main reasons your organization decided to adopt cloud computing?"
        },
        {
          "type": "multiple_choice",
          "label": "How satisfied are you with the security and reliability of your cloud service provider?",
          "options": ["Very satisfied", "Satisfied", "Neutral", "Dissatisfied", "Very dissatisfied"]
        },
        {
          "type": "single_choice",
          "label": "Have you encountered any challenges with scalability or performance using cloud services?",
          "options": ["Yes", "No", "Not applicable"]
        },
        {
          "type": "text",
          "label": "If yes, how have you addressed these challenges?"
        },
        {
          "type": "multiple_choice",
          "label": "How has cloud computing impacted the overall cost of your IT infrastructure?",
          "options": ["Significantly reduced costs", "Moderately reduced costs", "No significant change", "Moderately increased costs", "Significantly increased costs"]
        },
        {
          "type": "single_choice",
          "label": "Do you believe cloud computing has fostered increased collaboration and agility within your organization?",
          "options": ["Yes", "No", "Unsure"]
        },
        {
          "type": "text",
          "label": "How has cloud computing impacted your organization's disaster recovery capabilities?"
        },
        {
          "type": "multiple_choice",
          "label": "What are some of the biggest concerns your organization has regarding cloud computing?",
          "options": ["Data security and privacy", "Vendor lock-in", "Scalability limitations", "Integration with existing infrastructure", "All of the above"]
        },
        {
          "type": "text",
          "label": "What are some key factors you consider when choosing a cloud service provider?"
        },
        {
          "type": "single_choice",
          "label": "How likely are you to increase your reliance on cloud computing services in the future?",
          "options": ["Very likely", "Likely", "Neutral", "Somewhat unlikely", "Very unlikely"]
        },
        {
          "type": "text",
          "label": "What are your overall expectations for the future of cloud computing?"
        },
        {
          "type": "text",
          "label": "Do you have any additional comments or feedback regarding your organization's use of cloud computing?"
        }
      ]
    },
    {
      "title": "Software Development Lifecycle (SDLC) Practices Survey",
      "description": "Share your insights on your organization's approach to the SDLC!",
      "estimatedTime": "7 minutes",
      "id": "6",
      "questions": [
        {
          "type": "multiple_choice",
          "label": "Which SDLC methodology does your organization primarily follow?",
          "options": ["Agile (e.g., Scrum, Kanban)", "Waterfall", "Iterative development", "DevOps", "Other(please specify)", "None(we don't have a formal SDLC)"]
        },
        {
          "type": "single_choice",
          "label": "How involved are developers in the planning and requirements gathering stage of the SDLC?",
          "options": ["Highly involved", "Somewhat involved", "Limited involvement", "Not involved at all"]
        },
        {
          "type": "text",
          "label": "How do you ensure effective communication and collaboration between different development teams (e.g., frontend, backend, QA)?"
        },
        {
          "type": "multiple_choice",
          "label": "To what extent are unit testing and integration testing utilized within your development process?",
          "options": ["Extensively used throughout the entire development cycle", "Used regularly but not for every component", "Used occasionally or for critical components only", "Rarely or not used at all"]
        },
        {
          "type": "single_choice",
          "label": "Does your organization have a formal code review process in place?",
          "options": ["Yes", "No", "We have an informal code review process"]
        },
        {
          "type": "text",
          "label": "If yes, how do you find code reviews contribute to the quality and maintainability of your codebase?"
        },
        {
          "type": "multiple_choice",
          "label": "How often does your organization deploy new software versions to production?",
          "options": ["Multiple times per day (continuous deployment)", "Several times per week (continuous integration/continuous delivery)", "Weekly or bi-weekly deployments", "Monthly deployments or less frequent", "Other (please specify)"]
        },
        {
          "type": "single_choice",
          "label": "Does your organization have a dedicated team responsible for monitoring and maintaining deployed software?",
          "options": ["Yes", "No", "Our development teams handle these responsibilities"]
        },
        {
          "type": "text",
          "label": "How does your organization handle bug fixes and security vulnerabilities discovered after deployment?"
        },
        {
          "type": "multiple_choice",
          "label": "What tools and methodologies do you find most valuable for managing and tracking the SDLC process?",
          "options": ["Project management tools (e.g., Jira, Asana)", "Version control systems (e.g., Git)", "Issue tracking and bug reporting tools", "Continuous integration/continuous delivery (CI/CD) pipelines", "All of the above"]
        },
        {
          "type": "single_choice",
          "label": "How satisfied are you with the overall efficiency and effectiveness of your organization's SDLC practices?",
          "options": ["Very satisfied", "Satisfied", "Neutral", "Dissatisfied", "Very dissatisfied"]
        },
        {
          "type": "text",
          "label": "What are some specific areas where you believe your organization's SDLC could be improved?"
        },
        {
          "type": "multiple_choice",
          "label": "How open is your organization to adopting new technologies and methodologies to enhance the SDLC?",
          "options": ["Very open and adaptable", "Somewhat open to new ideas", "Neutral", "Hesitant to adopt new approaches", "Resistant to change"]
        },
        {
          "type": "text",
          "label": "What are your thoughts on the importance of continuous learning and skill development for SDLC professionals?"
        },
        {
          "type": "text",
          "label": "Do you have any additional suggestions or feedback regarding your organization's SDLC practices?"
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
            <IonMenuButton style={{ "--color": "var(--ion-background-light)" }}></IonMenuButton>
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








// const [surveys, setSurveys] = useState<any[]>([]);

// useEffect(() => {
//   fetch('path/to/your/surveys.json')
//     .then(response => response.json())
//     .then(data => setSurveys(data))
//     .catch(error => console.error('Error fetching surveys:', error));
// }, []);