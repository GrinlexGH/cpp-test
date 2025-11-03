import json
import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_benchmark_data(json_file_path):
    try:
        with open(json_file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except FileNotFoundError:
        print(f"Error: could not find '{json_file_path}'.")
        return
    except json.JSONDecodeError:
        print(f"Error: could not decode JSON from file '{json_file_path}'.")
        return
    except Exception as e:
        print(f"Unexcepcted error: {e}")
        return

    df = pd.DataFrame(data['benchmarks'])

    df_mean = df[df['aggregate_name'] == 'mean'].copy()

    if df_mean.empty:
        print("Error: could not find record with 'aggregate_name' == 'mean'.")
        return

    df_mean['simple_name'] = df_mean['name'].apply(
        lambda x: x.split('/')[0].replace('BM_', '')
    )

    names = df_mean['simple_name']
    times = df_mean['real_time']

    time_unit = df_mean['time_unit'].iloc[0]

    plt.figure(figsize=(10, 6))

    bars = plt.bar(names, times, color=['#007ACC', '#FFB900', '#E83E8C'])

    plt.bar_label(bars, fmt='%.2f')

    plt.xlabel('Structure type', fontsize=12)
    plt.ylabel(f'Average real time ({time_unit})', fontsize=12)
    plt.title('Bitfields test', fontsize=14, fontweight='bold')

    plt.grid(axis='y', linestyle='--', alpha=0.7)

    plt.tight_layout()

    output_filename = 'benchmark_plot.png'
    plt.savefig(output_filename)

    print(f"Graph successfully saved to {output_filename}")

    plt.show()

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    json_path = os.path.join(script_dir, "benchmark.json")

    plot_benchmark_data(json_path)