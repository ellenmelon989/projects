import { Component } from '@angular/core'
import { CommonModule } from '@angular/common'
import { FormsModule } from '@angular/forms'
import { PoetryService } from './poetry.service'

interface Poem {
  title: string
  author: string
  lines: string[]
  linecount: string
}

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  author = ''
  title = ''
  showCount = 5
  poems: Poem[] = []
  loading = false
  error = ''
  private expanded = new Set<string>()

  constructor(private api: PoetryService) {}
  private poemKey(p: any) {
    return `${p.author}|||${p.title}`
  }

  isExpanded(p: any): boolean {
    // console.log(this.expanded.has(this.poemKey(p)))
    return this.expanded.has(this.poemKey(p))
  }

  toggleExpand(p: any) {
    const k = this.poemKey(p)
    if (this.expanded.has(k)) this.expanded.delete(k)
    else this.expanded.add(k)
  }

  search() {
    this.error = ''
    this.loading = true
    this.poems = []
    this.api.search(this.author, this.title).subscribe({
      next: data => {
        this.poems = data
        this.loading = false
      },
      error: err => {
        this.error = String(err?.message || err)
        this.loading = false
      }
    })
  }

  clear() {
    this.author = ''
    this.title = ''
    this.poems = []
    this.error = ''
  }
}
