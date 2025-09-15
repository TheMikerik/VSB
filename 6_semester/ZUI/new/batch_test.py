import subprocess
import re

NUM_RUNS = 6
SOLVERS = ['rand', 'minmax', 'monte']
all_results = {}

for solver in SOLVERS:
    scores = []
    highest_tiles = []
    print(f"\n=== Testing solver: {solver} ===")
    for i in range(NUM_RUNS):
        print(f"Running game {i+1}/{NUM_RUNS}...")
        result = subprocess.run(["python3", "2048.py", solver], capture_output=True, text=True)
        
        score_match = re.search(r"FINAL_SCORE: (\d+)", result.stdout)
        tile_match = re.search(r"HIGHEST_TILE: (\d+)", result.stdout)
        
        if score_match:
            score = int(score_match.group(1))
            scores.append(score)
            print(f"Score: {score}")
        else:
            print("⚠️  No score found in output")
            
        if tile_match:
            highest_tile = int(tile_match.group(1))
            highest_tiles.append(highest_tile)
            print(f"Highest tile: {highest_tile}")
        else:
            print("⚠️  No highest tile found in output")
    
    # Store results for this solver but don't print detailed stats yet
    if scores:
        all_results[solver] = {
            "games_played": len(scores),
            "average_score": sum(scores) / len(scores),
            "max_score": max(scores),
            "min_score": min(scores),
            "highest_tiles": highest_tiles,
            "max_tile_reached": max(highest_tiles) if highest_tiles else 0,
            "tile_frequencies": {
                tile: highest_tiles.count(tile) 
                for tile in sorted(set(highest_tiles), reverse=True)
            } if highest_tiles else {}
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
        print(f"Highest tile reached: {results['max_tile_reached']}")
        print(f"Tile frequencies:")
        for tile, frequency in results['tile_frequencies'].items():
            percentage = (frequency / results['games_played']) * 100
            print(f"  {tile}: {frequency} times ({percentage:.1f}%)")