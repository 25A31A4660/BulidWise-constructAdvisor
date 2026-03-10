#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Structures to hold data ---

typedef struct {
    char name[50];
    char composition[200];
    char manufacturing_process[300];
    float price_india;      // Price per unit in INR
    float price_foreign;    // Price per unit in USD
    float import_duty;      // Percentage tax
    float shipping_charge;  // Flat rate per unit
} Material;

typedef struct {
    char type[50];
    char skill_level[100];
    float daily_wage;
} Labor;

// --- Function Prototypes ---
void main_menu();
void project_advisor();
void material_encyclopedia();
void labor_info();
void calculate_material_cost(int material_id, float area);
void show_material_details(int material_id);

// --- Global Data (Simulated Database) ---
// In a real app, these might come from a file, but for C logic, we initialize them here.
Material materials[3] = {
    {
        "Portland Pozzolana Cement (PPC)",
        "Clinker + Gypsum + Fly Ash",
        "Grinding clinker with gypsum and pozzolanic materials. Good for general use.",
        450.0,  // INR per bag
        8.0,    // USD per bag
        12.0,   // 12% Import duty
        50.0    // Shipping per bag
    },
    {
        "TMT Steel Bars (Fe-500)",
        "Iron + Carbon + Manganese",
        "Thermo-Mechanical Treatment process. Quenching and self-tempering.",
        65.0,   // INR per kg
        1.2,    // USD per kg
        18.0,   // 18% Import duty
        10.0    // Shipping per kg
    },
    {
        "Red Clay Bricks",
        "Alumina + Silica + Lime",
        "Molding clay, drying, and burning in kilns at high temperature.",
        12.0,   // INR per piece
        0.5,    // USD per piece
        5.0,    // 5% Duty
        2.0     // Shipping
    }
};

Labor labors[3] = {
    {"Head Mason", "Highly Skilled - 10+ Years Exp", 1200.0},
    {"General Helper", "Unskilled - Physical Labor", 500.0},
    {"Site Engineer", "Professional - B.Tech Civil", 2500.0}
};

// --- Main Function ---
int main() {
    printf("=================================================\n");
    printf("   WELCOME TO BUILDWISE: CONSTRUCTION ADVISOR    \n");
    printf("=================================================\n");
    
    while(1) {
        main_menu();
    }
    return 0;
}

void main_menu() {
    int choice;
    printf("\n--- MAIN MENU ---\n");
    printf("1. Project Advisor (Plan a Building)\n");
    printf("2. Material Encyclopedia (Details & Quality)\n");
    printf("3. Labor Market Info\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: project_advisor(); break;
        case 2: material_encyclopedia(); break;
        case 3: labor_info(); break;
        case 4: 
            printf("Exiting BuildWise. Good luck with construction!\n");
            exit(0);
        default: printf("Invalid choice. Try again.\n");
    }
}

// --- Feature 1: The Context/Location Logic ---
void project_advisor() {
    int build_type, terrain_type;
    float area;

    printf("\n--- STEP 1: BUILDING TYPE ---\n");
    printf("1. Residential (Home/Apts)\n");
    printf("2. Commercial (Shops/Malls)\n");
    printf("3. Industrial (Factories)\n");
    printf("Select Type: ");
    scanf("%d", &build_type);

    printf("\n--- STEP 2: TERRAIN / LOCATION ---\n");
    printf("1. Normal Plains\n");
    printf("2. Hilly Area\n");
    printf("3. Coastal / Sea Side\n");
    printf("4. Underground\n");
    printf("Select Terrain: ");
    scanf("%d", &terrain_type);

    printf("\n--- STEP 3: AREA ---\n");
    printf("Enter Total Area (sq. ft): ");
    scanf("%f", &area);

    printf("\n\n>>> ANALYZING PROJECT REQUIREMENTS <<<\n");
    
    // Logic: Suggesting based on Terrain
    if (terrain_type == 2) { // Hill
        printf("[ADVICE]: You are building on Hilly Terrain.\n");
        printf(" - Feature: Step foundation recommended.\n");
        printf(" - Material Note: Use lightweight concrete blocks to reduce load.\n");
    } else if (terrain_type == 3) { // Sea
        printf("[ADVICE]: You are building near the Sea.\n");
        printf(" - Feature: Anti-corrosive coating is MANDATORY.\n");
        printf(" - Material Note: Use Sulphate Resisting Cement (SRC) instead of normal PPC.\n");
    } else if (terrain_type == 4) { // Underground
        printf("[ADVICE]: Underground Construction.\n");
        printf(" - Feature: Heavy waterproofing required.\n");
        printf(" - Material Note: High-grade reinforced concrete (M40 grade) required.\n");
    } else {
        printf("[ADVICE]: Standard Construction.\n");
        printf(" - Standard brick masonry and RCC frame structure.\n");
    }

    printf("\nDo you want to check specific material costs for this area? (1 for Yes / 0 for No): ");
    int check;
    scanf("%d", &check);
    if(check == 1) {
        material_encyclopedia();
    }
}

// --- Feature 2: Material Details & Comparison ---
void material_encyclopedia() {
    int mat_choice;
    printf("\n--- MATERIAL ENCYCLOPEDIA ---\n");
    printf("Select a material to analyze:\n");
    printf("1. Cement (PPC)\n");
    printf("2. Steel (TMT)\n");
    printf("3. Bricks (Red Clay)\n");
    printf("Enter choice: ");
    scanf("%d", &mat_choice);

    if (mat_choice < 1 || mat_choice > 3) {
        printf("Invalid material selection.\n");
        return;
    }

    // Adjust index for array (0-2)
    show_material_details(mat_choice - 1);
}

void show_material_details(int id) {
    Material m = materials[id];
    
    printf("\n-------------------------------------------------\n");
    printf("MATERIAL: %s\n", m.name);
    printf("-------------------------------------------------\n");
    printf("COMPOSITION: %s\n", m.composition);
    printf("PROCESS: %s\n", m.manufacturing_process);
    
    printf("\n--- PRICING ANALYSIS ---\n");
    printf("1. Domestic Price (India): %.2f INR per unit\n", m.price_india);
    
    // Simple conversion (Example: 1 USD = 83 INR)
    float foreign_inr = m.price_foreign * 83.0; 
    printf("2. Foreign Price (Global): %.2f USD (Approx %.2f INR)\n", m.price_foreign, foreign_inr);
    
    printf("\nWould you like a detailed Import Cost breakdown? (1 for Yes / 0 for No): ");
    int calc;
    scanf("%d", &calc);
    
    if(calc == 1) {
        float import_tax = (foreign_inr * m.import_duty) / 100;
        float total_import_cost = foreign_inr + import_tax + m.shipping_charge;
        
        printf("\n--- IMPORT COST BREAKDOWN ---\n");
        printf("Base Cost:       %.2f INR\n", foreign_inr);
        printf("Import Duty (%.0f%%): %.2f INR\n", m.import_duty, import_tax);
        printf("Shipping Charge: %.2f INR\n", m.shipping_charge);
        printf("-------------------------\n");
        printf("TOTAL LANDED COST: %.2f INR\n", total_import_cost);
        
        if(total_import_cost > m.price_india) {
            printf("\n[VERDICT]: Buying LOCALLY in India is cheaper by %.2f INR.\n", total_import_cost - m.price_india);
        } else {
            printf("\n[VERDICT]: IMPORTING is cheaper by %.2f INR.\n", m.price_india - total_import_cost);
        }
    }
}

// --- Feature 3: Labor Info ---
void labor_info() {
    printf("\n--- LABOR MARKET INFORMATION ---\n");
    printf("Finding skilled labor is critical for durability.\n\n");
    printf("%-20s %-35s %-15s\n", "ROLE", "SKILL REQUIRED", "DAILY WAGE (INR)");
    printf("--------------------------------------------------------------------------\n");
    
    for(int i=0; i<3; i++) {
        printf("%-20s %-35s %.2f\n", labors[i].type, labors[i].skill_level, labors[i].daily_wage);
    }
    printf("--------------------------------------------------------------------------\n");
    printf("\nPress any key (enter) to return to menu...");
    getchar(); getchar(); // Capture newline buffer
}