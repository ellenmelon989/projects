import { Injectable } from '@angular/core'
import { HttpClient, HttpErrorResponse, HttpResponse } from '@angular/common/http'
import { Observable, forkJoin, of, throwError } from 'rxjs'
import { catchError, map } from 'rxjs/operators'

interface Poem {
  title: string
  author: string
  lines: string[]
  linecount: string
}

const BASE = 'https://poetrydb.org'

@Injectable({ providedIn: 'root' })
export class PoetryService {
  constructor(private http: HttpClient) {}

  private normalizePoem(p: any): Poem {
    const lines = Array.isArray(p?.lines)
      ? p.lines
      : (typeof p?.lines === 'string' ? p.lines.split(/\r?\n/) : [])
    const linecount = p?.linecount != null ? String(p.linecount) : String(lines.length)
    return {
      title: p?.title ?? '',
      author: p?.author ?? '',
      lines,
      linecount
    }
  }
  private getOk<T>(url: string): Observable<T> {
    return this.http.get<T>(url, { observe: 'response' }).pipe(
      map((res: HttpResponse<T>) => {
        if (res.status !== 200) {
          throw new Error(`Request failed with status ${res.status}`)
        }
        if (res.body == null) {
          throw new Error('Empty response body')
        }
        return res.body
      }),
      catchError((err: HttpErrorResponse) => {
        const msg = err.error?.reason || err.message || 'Network error'
        return throwError(() => new Error(msg))
      })
    )
  }

  searchByAuthor(author: string): Observable<Poem[]> {
    const a = author.trim()
    if (!a) return of([])
    const url = `${BASE}/author/${encodeURIComponent(a)}`
    return this.getOk<Poem[]>(url).pipe(
      map((arr: any) => (Array.isArray(arr) ? arr.map(p => this.normalizePoem(p)) : [])))
  }

  searchByTitle(title: string): Observable<Poem[]> {
    const t = title.trim()
    if (!t) return of([])
    const url = `${BASE}/title/${encodeURIComponent(t)}`
    return this.getOk<Poem[]>(url).pipe(
      map((arr: any) => (Array.isArray(arr) ? arr.map(p => this.normalizePoem(p)) : []))
    )
  }

  search(author: string, title: string): Observable<Poem[]> {
    const a = author.trim()
    const t = title.trim()
    if (a && !t) return this.searchByAuthor(a)
    if (!a && t) return this.searchByTitle(t)
    if (!a && !t) return of([])
    return forkJoin([
      this.searchByAuthor(a).pipe(catchError(() => of([]))),
      this.searchByTitle(t).pipe(catchError(() => of([])))
    ]).pipe(
      map(([byAuthor, byTitle]) => {
        const authorArr = Array.isArray(byAuthor) ? byAuthor : []
        const titleArr = Array.isArray(byTitle) ? byTitle : []
        const key = (p: Poem) => `${p.author}|||${p.title}`
        const byTitleSet = new Set(titleArr.map(key))
        return authorArr.filter(p => byTitleSet.has(key(p)))
      })
    )
  }
}
