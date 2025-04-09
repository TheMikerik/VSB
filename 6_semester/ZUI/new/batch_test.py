import subprocess
import re

NUM_RUNS = 15
SOLVERS = ['rand', 'minmax', 'monte']
all_results = {}

for solver in SOLVERS:
    scores = []
    print(f"\n=== Testing solver: {solver} ===")
    for i in range(NUM_RUNS):
        print(f"Running game {i+1}/{NUM_RUNS}...")
        result = subprocess.run(["python3", "2048.py", solver], capture_output=True, text=True)
        
        match = re.search(r"FINAL_SCORE: (\d+)", result.stdout)
        if match:
            score = int(match.group(1))
            scores.append(score)
            print(f"Score: {score}")
        else:
            print("⚠️  No score found in output")
    
    # Store results for this solver but don't print detailed stats yet
    if scores:
        all_results[solver] = {
            "games_played": len(scores),
            "average_score": sum(scores) / len(scores),
            "max_score": max(scores),
            "min_score": min(scores)
        }
    else:
        all_results[solver] = {"error": "No valid scores"}

# Print final results for all solvers at once
print("\n\n==== FINAL RESULTS ====")
for solver, results in all_results.items():
    print(f"\n✅ Solver: {solver}")
    if "error" in results:
        print(f"❌ {results['error']}")
    else:
        print(f"Games played: {results['games_played']}")
        print(f"Average score: {results['average_score']:.2f}")
        print(f"Max score: {results['max_score']}")
        print(f"Min score: {results['min_score']}")