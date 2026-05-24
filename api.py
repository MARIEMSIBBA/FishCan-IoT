# main.py

from fastapi import FastAPI
from pydantic import BaseModel
import csv
import os

app = FastAPI()

# ── stockage mémoire ──
database = []

# ── fichier CSV ──
CSV_FILE = "fishcan_data.csv"

# ── modèle données ──
class SensorData(BaseModel):
    temperature: float
    torque: float
    vibration: float
    F0: float
    seaming_status: str
    sterilization_status: str

# ── créer CSV si n'existe pas ──
if not os.path.exists(CSV_FILE):
    with open(CSV_FILE, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([
            "temperature",
            "torque",
            "vibration",
            "F0",
            "seaming_status",
            "sterilization_status"
        ])

# ── recevoir données ESP32 ──
@app.post("/data")
def receive_data(data: SensorData):

    print("\n===== DATA RECEIVED FROM ESP32 =====")
    print(data)

    # ✔ stockage mémoire
    database.append(data.dict())

    # ✔ sauvegarde CSV automatique
    with open(CSV_FILE, "a", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([
            data.temperature,
            data.torque,
            data.vibration,
            data.F0,
            data.seaming_status,
            data.sterilization_status
        ])

    return {"message": "Data saved to CSV"}

# ── récupérer toutes les données (mémoire) ──
@app.get("/data")
def get_data():
    return {
        "total": len(database),
        "data": database
    }

# ── récupérer dernière donnée ──
@app.get("/last")
def get_last():
    if len(database) == 0:
        return {"message": "No data"}
    return database[-1]

# ── lire directement le CSV (IMPORTANT pour AI) ──
@app.get("/csv")
def get_csv_data():
    data = []
    with open(CSV_FILE, "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            data.append(row)
    return {
        "total": len(data),
        "data": data
    }

# ── supprimer tout ──
@app.delete("/clear")
def clear_data():
    database.clear()

    # vider CSV
    with open(CSV_FILE, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([
            "temperature",
            "torque",
            "vibration",
            "F0",
            "seaming_status",
            "sterilization_status"
        ])

    return {"message": "All data cleared"}