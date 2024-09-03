type ListenerType = (...args: any[]) => unknown;
export class EventDispatcher {
    private listeners: { [key: string]: ListenerType[] } = {};
    emit(event: string, ...args: any[]): void {
        if (this.listeners[event]) {
            this.listeners[event].forEach((listener) => listener(...args));
        }
    }
}