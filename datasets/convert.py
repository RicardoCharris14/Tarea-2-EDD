# Convierte la columna user_id a notacion decimal

import pandas as pd

df = pd.read_csv("universities_followers.csv")
df = df.astype({"user_id": int})
df.to_csv("dataset.csv", sep=',', index=False)

