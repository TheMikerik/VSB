class Run {
  String runID;
  String userID;
  double distance; // in kilometers
  Duration duration; // in TimeSpan
  DateTime date;

  // Constructor
  Run({
    required this.runID,
    required this.userID,
    required this.distance,
    required this.duration,
    required this.date,
  });

  void startRun() {
    // Logic to start the run
    print("Run $runID started for user $userID.");
  }

  void endRun() {
    // Logic to end the run
    print("Run $runID ended for user $userID.");
  }

  String getRunDetails() {
    return 'Run ID: $runID\n'
        'User ID: $userID\n'
        'Distance: ${distance.toString()} km\n'
        'Duration: ${duration.inMinutes} minutes\n'
        'Date: ${date.toLocal()}';
  }
}

// Example of how to use the Run class
void main() {
  // Create a new run instance
  Run myRun = Run(
    runID: '001',
    userID: 'user123',
    distance: 5.0,
    duration: Duration(minutes: 30),
    date: DateTime.now(),
  );

  // Start the run
  myRun.startRun();

  // End the run
  myRun.endRun();

  // Get run details
  print(myRun.getRunDetails());
}
