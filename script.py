import subprocess
import threading

def read_output(process, label):
    while True:
        output = process.stdout.readline().decode().strip()
        if output:
            print(f"[{label}]: {output}")
        if process.poll() is not None:
            break

def run_concurrent():
    cmd1 = [
        'sudo', '/usr/local/sbin/ts2phc', '-c', '/dev/ptp0', '-s', 'generic',
        '--ts2phc.extts_correction', '-1', '--ts2phc.extts_polarity', 'rising',
        '--ts2phc.pin_index', '0', '--leapfile', '/usr/share/zoneinfo/leap-seconds.list',
        '--ts2phc.channel', '2', '-l', '7', '-m'
    ]
    # Replace directory DMTIMER-Capture with your cloned directory
    cmd2 = ['sudo', '/home/debian/DMTIMER-Capture/Main/main']

    process1 = subprocess.Popen(cmd1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process2 = subprocess.Popen(cmd2, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # Start separate threads to read outputs concurrently
    t1 = threading.Thread(target=read_output, args=(process1, "ts2phc"))
    t2 = threading.Thread(target=read_output, args=(process2, "main"))
    
    t1.start()
    t2.start()

    # Wait for both threads to finish
    t1.join()
    t2.join()

    print("Both processes have exited.")

if __name__ == "__main__":
    run_concurrent()
