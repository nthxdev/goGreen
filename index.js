import jsonfile from 'jsonfile';
import moment from 'moment';
import simpleGit from 'simple-git';
import random from 'random';

// =========================================================
// [ 1. GLOBAL CONFIGURATION ]
// =========================================================
// Modify these variables to change the graph's density and temporal anchor.

// FILE_PATH: The dummy file used to force a Git tree change. 
// Git strictly requires a file diff to instantiate a new commit object.
const FILE_PATH = './data.json'; 

// TARGET_YEARS_BACK: Defines the temporal anchor (how far back the graph starts).
// Change to 2 for the previous year, 5 for five years ago, etc.
const TARGET_YEARS_BACK = 1; 

// TOTAL_COMMITS: Dictates the density of the contribution graph.
// Higher numbers = darker green squares. 
// Warning: Setting this > 1000 may hit V8 call stack size limits or GitHub remote rejection.
const TOTAL_COMMITS = 100;

// Toggle mode between 'ART' & 'RANDOM'
const MODE = 'ART';

// =========================================================
// [ 2. GRADIENT INTENSITY MULTIPLIERS ]
// Maps the UI brush level (1-4) to the number of commits stacked on a single day.
// =========================================================
const LEVEL_MULTIPLIERS = {
    1: 1,   // Light green
    2: 4,   // Medium green
    3: 8,   // Dark green
    4: 12   // Darkest green
};

// =========================================================
// [ 3. VECTOR MATRICES (PIXEL ART) ]
// GitHub Graph = 53 Columns (Weeks) x 7 Rows (Days)
// =========================================================

// Example: Space Invader / Cat Face icon with gradient levels.
// Visual Map (X offset by 10 weeks to center it):
// Y=1:   [11]      [15]       (Ears)
// Y=2:      [12][13][14]      (Top Head)
// Y=3:   [11][12][13][14][15] (Upper Face)
// Y=4:   [11]   [13]   [15]   (Eyes)
// Y=5:   [11][12][13][14][15] (Lower Face)
// Y=6:      [12]    [14]      (Legs)
//
// The 'level' property controls commit density:
// - Higher levels stack more commits on the same day for darker gradient colors
// const ART_SHAPE = [
//     {x: 11, y: 1, level: 4}, {x: 15, y: 1, level: 4},
//     {x: 12, y: 2, level: 4}, {x: 13, y: 2, level: 4}, {x: 14, y: 2, level: 4},
//     {x: 11, y: 3, level: 4}, {x: 12, y: 3, level: 4}, {x: 13, y: 3, level: 4}, {x: 14, y: 3, level: 4}, {x: 15, y: 3, level: 4},
//     {x: 11, y: 4, level: 4}, {x: 13, y: 4, level: 4}, {x: 15, y: 4, level: 4},
//     {x: 11, y: 5, level: 4}, {x: 12, y: 5, level: 4}, {x: 13, y: 5, level: 4}, {x: 14, y: 5, level: 4}, {x: 15, y: 5, level: 4},
//     {x: 12, y: 6, level: 4}, {x: 14, y: 6, level: 4}
// ];
const ART_SHAPE = [
    {x: 2, y: 0}, {x: 3, y: 0}, {x: 17, y: 0}, {x: 20, y: 0}, {x: 22, y: 0}, 
    {x: 23, y: 0}, {x: 24, y: 0}, {x: 1, y: 1}, {x: 2, y: 1}, {x: 3, y: 1}, 
    {x: 12, y: 1}, {x: 13, y: 1}, {x: 14, y: 1}, {x: 15, y: 1}, {x: 16, y: 1}, 
    {x: 17, y: 1}, {x: 18, y: 1}, {x: 19, y: 1}, {x: 21, y: 1}, {x: 22, y: 1}, 
    {x: 23, y: 1}, {x: 24, y: 1}, {x: 29, y: 1}, {x: 30, y: 1}, {x: 31, y: 1}, 
    {x: 32, y: 1}, {x: 33, y: 1}, {x: 34, y: 1}, {x: 35, y: 1}, {x: 36, y: 1}, 
    {x: 41, y: 1}, {x: 42, y: 1}, {x: 43, y: 1}, {x: 1, y: 2}, {x: 2, y: 2}, 
    {x: 3, y: 2}, {x: 5, y: 2}, {x: 7, y: 2}, {x: 8, y: 2}, {x: 10, y: 2}, 
    {x: 11, y: 2}, {x: 13, y: 2}, {x: 14, y: 2}, {x: 15, y: 2}, {x: 16, y: 2}, 
    {x: 17, y: 2}, {x: 18, y: 2}, {x: 19, y: 2}, {x: 21, y: 2}, {x: 22, y: 2}, 
    {x: 23, y: 2}, {x: 24, y: 2}, {x: 25, y: 2}, {x: 26, y: 2}, {x: 27, y: 2}, 
    {x: 28, y: 2}, {x: 29, y: 2}, {x: 30, y: 2}, {x: 32, y: 2}, {x: 33, y: 2}, 
    {x: 36, y: 2}, {x: 37, y: 2}, {x: 39, y: 2}, {x: 40, y: 2}, {x: 41, y: 2}, 
    {x: 42, y: 2}, {x: 43, y: 2}, {x: 44, y: 2}, {x: 47, y: 2}, {x: 3, y: 3}, 
    {x: 4, y: 3}, {x: 5, y: 3}, {x: 6, y: 3}, {x: 7, y: 3}, {x: 8, y: 3}, 
    {x: 9, y: 3}, {x: 11, y: 3}, {x: 13, y: 3}, {x: 14, y: 3}, {x: 15, y: 3}, 
    {x: 16, y: 3}, {x: 17, y: 3}, {x: 18, y: 3}, {x: 19, y: 3}, {x: 20, y: 3}, 
    {x: 21, y: 3}, {x: 26, y: 3}, {x: 27, y: 3}, {x: 29, y: 3}, {x: 32, y: 3}, 
    {x: 33, y: 3}, {x: 34, y: 3}, {x: 35, y: 3}, {x: 37, y: 3}, {x: 40, y: 3}, 
    {x: 46, y: 3}, {x: 48, y: 3}, {x: 3, y: 4}, {x: 4, y: 4}, {x: 6, y: 4}, 
    {x: 7, y: 4}, {x: 8, y: 4}, {x: 10, y: 4}, {x: 11, y: 4}, {x: 13, y: 4}, 
    {x: 14, y: 4}, {x: 15, y: 4}, {x: 16, y: 4}, {x: 17, y: 4}, {x: 18, y: 4}, 
    {x: 19, y: 4}, {x: 23, y: 4}, {x: 24, y: 4}, {x: 25, y: 4}, {x: 27, y: 4}, 
    {x: 28, y: 4}, {x: 29, y: 4}, {x: 30, y: 4}, {x: 31, y: 4}, {x: 32, y: 4}, 
    {x: 33, y: 4}, {x: 35, y: 4}, {x: 36, y: 4}, {x: 37, y: 4}, {x: 40, y: 4}, 
    {x: 45, y: 4}, {x: 46, y: 4}, {x: 48, y: 4}, {x: 3, y: 5}, {x: 4, y: 5}, 
    {x: 6, y: 5}, {x: 8, y: 5}, {x: 9, y: 5}, {x: 10, y: 5}, {x: 11, y: 5}, 
    {x: 12, y: 5}, {x: 13, y: 5}, {x: 14, y: 5}, {x: 15, y: 5}, {x: 16, y: 5}, 
    {x: 17, y: 5}, {x: 20, y: 5}, {x: 21, y: 5}, {x: 22, y: 5}, {x: 23, y: 5}, 
    {x: 24, y: 5}, {x: 25, y: 5}, {x: 26, y: 5}, {x: 27, y: 5}, {x: 28, y: 5}, 
    {x: 29, y: 5}, {x: 30, y: 5}, {x: 31, y: 5}, {x: 32, y: 5}, {x: 33, y: 5}, 
    {x: 34, y: 5}, {x: 35, y: 5}, {x: 36, y: 5}, {x: 37, y: 5}, {x: 38, y: 5}, 
    {x: 39, y: 5}, {x: 42, y: 5}, {x: 43, y: 5}, {x: 44, y: 5}, {x: 6, y: 6}, 
    {x: 7, y: 6}, {x: 8, y: 6}, {x: 9, y: 6}, {x: 10, y: 6}, {x: 22, y: 6}, 
    {x: 23, y: 6}, {x: 27, y: 6}, {x: 28, y: 6}, {x: 29, y: 6}, {x: 30, y: 6}, 
    {x: 34, y: 6}, {x: 35, y: 6}, {x: 39, y: 6}, {x: 40, y: 6}, {x: 41, y: 6}
];

// =========================================================

const git = simpleGit();

const makeCommit = async (n, artIndex = 0) => {

    // Base Case Check: Did we finish iterating the array OR hit 0 random commits?
    const isFinished = MODE === 'ART' ? (artIndex >= ART_SHAPE.length) : (n === 0);

    // Base Case: Network Execution
    // Executes a single `git push` only after the entire recursive loop finishes building the local tree.
    if (isFinished) {
        console.log("Local generation complete. Pushing payload to remote...");
        await git.push();
        return;
    }

    // =========================================================
    // [ 4. COORDINATE & INTENSITY RESOLUTION ]
    // The GitHub contribution graph is a 2D Matrix (Weeks x Days).
    // =========================================================
    let x, y, levelCount = 1;
    
    if (MODE === 'ART') {
        // Deterministic mapping: Extract explicit coordinates from the vector array
        x = ART_SHAPE[artIndex].x;
        y = ART_SHAPE[artIndex].y;
        
        // Default to darkest green (level 4) if the array is missing the level property
        // This allows for gradient control via multiple commits on the same timestamp
        const targetLevel = ART_SHAPE[artIndex].level || 4; 
        levelCount = LEVEL_MULTIPLIERS[targetLevel];
    } else {
        // Stochastic mapping: Fallback to random generation
        // X-Axis (Weeks): A calendar year has 52-54 weeks depending on leap years/start days.
        // Replace `random.int(0, 54)` with a static number to target a specific column.
        x = random.int(0, 54); 
        // Y-Axis (Days): 0 represents Sunday, 6 represents Saturday.
        // Replace `random.int(0, 6)` with a static number to target a specific row.
        y = random.int(0, 6); 
    }
    
    // =========================================================
    // [ 5. TEMPORAL MUTATION ]
    // Constructs the exact timestamp injected into the Git commit header.
    // =========================================================
    const DATE = moment()
        .subtract(TARGET_YEARS_BACK, 'y') // Jump back in time
        .add(1, 'd')                      // Base offset
        .add(x, 'w')                      // Shift horizontally on the graph (weeks)
        .add(y, 'd')                      // Shift vertically on the graph (days)
        .format();                        // Output ISO 8601 string
    // =========================================================

    const data = { date: DATE };
    
    // Execution Cycle: Disk I/O (Write) -> Stage (Add) -> Git Object Creation (Commit) -> Recurse
    // The '--date' flag is the core mechanic. It explicitly overrides 
    // the system clock for both AuthorDate and CommitDate within the Git binary.
    jsonfile.writeFile(FILE_PATH, data, async () => {
        
        // Inner Loop: Stacks multiple commits onto the exact same timestamp to force darker gradients
        // Multiple commits on the same date increase the visual intensity on GitHub's contribution graph
        for (let i = 0; i < levelCount; i++) {
            await git.add([FILE_PATH]).commit(DATE, { '--date': DATE });
        }
        
        // Progress to the next item in the art array or decrement random counter
        makeCommit(MODE === 'ART' ? 0 : --n, ++artIndex);
    });
};

// =========================================================
// [ ENGINE INITIALIZATION ]
// =========================================================
if (MODE === 'ART') {
    // Calculate total commits to print accurate logs
    // This accounts for the gradient multipliers applied to each coordinate
    const totalArtCommits = ART_SHAPE.reduce((sum, point) => sum + LEVEL_MULTIPLIERS[point.level || 4], 0);
    console.log(`Starting ART mode: Generating ${totalArtCommits} gradient commits across ${ART_SHAPE.length} coordinates...`);
    makeCommit(0, 0); // Ignore TOTAL_COMMITS, use array length
} else {
    console.log(`Starting RANDOM mode: Generating ${TOTAL_COMMITS} stochastic commits...`);
    makeCommit(TOTAL_COMMITS, 0);
}