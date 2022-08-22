export class Device {
  private id: string = "";
  private url: string = "";

  constructor(id: string, url: string) {
    this.id = id;
    this.url = url;
  }

  get deviceId(): string {
    return this.id;
  }

  get deviceUrl(): string {
    return this.url;
  }
}